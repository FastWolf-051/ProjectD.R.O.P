#include "Messaging.h"
#include "MessageManager.h"
#include "../Networking/Connection/ClientConnection.h"
#include "../../titan/Debug/Debugger.h"
#include "../../titan/DataStream/ByteStream.h"
#include "../../titan/Encryption/Library/TweetNaCl/TweetNaCl.h"
#include "../../titan/Encryption/Library/Blake/Blake2BHasher.h"

#include <cstring>
#include <vector>
#include <cstdio>

Messaging::Messaging(ClientConnection* connection)
    : _factory(new LogicSlashMessageFactory()),
      _encrypter(nullptr),
      _decrypter(nullptr),
      _pepperState(2),
      _clientPublicKey(nullptr),
      _sendNonce(nullptr),
      _receiveNonce(nullptr),
      _sharedKey(),
      _secretKey(nullptr),
      _connection(connection),
      _manager(nullptr) {

    _sendNonce = new unsigned char[24];
    TweetNaCl::RandomBytes(_sendNonce, 24);

    _secretKey = new unsigned char[32];
    TweetNaCl::RandomBytes(_secretKey, 32);

    _manager = new MessageManager(_connection);
}

int Messaging::OnReceive(unsigned char* buffer, int size) {
    int consumedBytes = 0;

    while (size >= HeaderSize) {
        int messageType;
        int length;
        short messageVersion;

        ReadHeader(buffer, messageType, length, messageVersion);

        if (length < 0) return -1;

        if (size < HeaderSize + length) break;

        size -= HeaderSize + length;
        consumedBytes += HeaderSize + length;

        unsigned char* encryptedBytes = new unsigned char[length];

        std::memcpy(encryptedBytes, buffer + HeaderSize, length);

        buffer += HeaderSize + length;

        unsigned char* clearBytes = nullptr;
        int clearLength = 0;

        switch (_pepperState) {
            case 2:
                if (messageType != 10100) {
                    delete[] encryptedBytes;
                    return -1;
                }

                _pepperState = 3;

                clearBytes = encryptedBytes;
                clearLength = length;

                encryptedBytes = nullptr;
                break;

            case 3:
                if (messageType != 10101) {
                    delete[] encryptedBytes;
                    return -1;
                }

                clearBytes = HandlePepperLogin(encryptedBytes, length, clearLength);

                delete[] encryptedBytes;

                if (clearBytes == nullptr)
                    return -1;

                break;

            case 5: {
                if (_decrypter == nullptr) {
                    delete[] encryptedBytes;
                    return -1;
                }

                int decryptedLength = length - _decrypter->GetOverheadEncryption();

                if (decryptedLength < 0) {
                    delete[] encryptedBytes;
                    return -1;
                }

                unsigned char* decrypted = new unsigned char[decryptedLength];

                int result = _decrypter->Decrypt(encryptedBytes, decrypted, length);

                delete[] encryptedBytes;

                if (result != 0) {
                    delete[] decrypted;
                    return -1;
                }

                clearBytes = decrypted;
                clearLength = decryptedLength;
            }
                break;

            default:
                delete[] encryptedBytes;
                return -1;
        }

        PiranhaMessage* message = _factory->CreateMessageByType(messageType);

        if (message != nullptr) {
            message->SetMessageVersion(messageVersion);

            ByteStream* stream = message->GetByteStream();

            if (stream == nullptr) {
                delete[] clearBytes;
                delete message;
                continue;
            }

            stream->SetByteArray(clearBytes, clearLength);

            delete[] clearBytes;
            clearBytes = nullptr;

            stream->ResetOffset();

            message->Decode();

            _manager->ReceiveMessage(message);

            delete message;
        }
        else {
            Debugger::Warning("Message of type %d isn't implemented", messageType);
        }
    }

    return consumedBytes;
}

void Messaging::Send(PiranhaMessage* message) {
    message->Encode();

    ByteStream* stream = message->GetByteStream();

    const int bodyLength = stream->GetOffset();

    unsigned char* streamBuffer = stream->GetByteArray();

    unsigned char* body = nullptr;

    if (bodyLength > 0) {
        body = new unsigned char[bodyLength];

        std::memcpy(body, streamBuffer, bodyLength);
    }

    unsigned char* toSend = nullptr;
    int sendLength = 0;

    switch (_pepperState) {
        case 4: {
            toSend = SendPepperLoginResponse(body, bodyLength, sendLength);

            delete[] body;
            body = nullptr;

            if (!toSend) return;

            break;
        }
        case 5: {
            if (!_encrypter) {
                delete[] body;
                return;
            }

            const int overhead = _encrypter->GetOverheadEncryption();

            sendLength = bodyLength + overhead;

            toSend = new unsigned char[sendLength];

            int result = _encrypter->Encrypt(body, toSend, bodyLength);

            delete[] body;
            body = nullptr;

            if (result != 0) {
                delete[] toSend;
                return;
            }

            break;
        }

        default: {
            sendLength = bodyLength;
            toSend = body;
            body = nullptr;
            break;
        }
    }

    if (sendLength < 0 || sendLength > 0xFFFFFF) {
        delete[] toSend;
        return;
    }

    const int packetLength = HeaderSize + sendLength;

    unsigned char* fullPayload = new unsigned char[packetLength];

    WriteHeader(fullPayload, message, sendLength);

    if (sendLength > 0) {
        std::memcpy(fullPayload + HeaderSize, toSend, sendLength);
    }

    _connection->Send(fullPayload, packetLength);

    delete[] toSend;
    delete[] fullPayload;
}

unsigned char* Messaging::HandlePepperLogin(const unsigned char* payload, int payloadLength, int& clearLength) {    
    clearLength = 0;

    delete[] _clientPublicKey;
    _clientPublicKey = nullptr;

    _clientPublicKey = new unsigned char[32];

    std::memcpy(_clientPublicKey, payload, 32);

    Blake2BHasher hasher;

    hasher.Update(_clientPublicKey, 0, 32);
    hasher.Update(PepperKey::SERVER_PK.data(), 0, 32);

    size_t hashLength = 0;

    unsigned char* hash = hasher.Finish(hashLength);

    unsigned char nonce[24];
    std::memcpy(nonce, hash, 24);

    delete[] hash;

    std::vector<unsigned char> client_pk(_clientPublicKey, _clientPublicKey + 32);

    _sharedKey = TweetNaCl::CryptoBoxBeforenm(client_pk, PepperKey::SERVER_SK);

    const unsigned char* wireCiphertext = payload + 32;
    const int wireCiphertextLength = payloadLength - 32;

    bytearray encrypted(wireCiphertext, wireCiphertext + wireCiphertextLength);

    bytearray decrypted = TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet_open(encrypted, bytearray(nonce, nonce + 24), _sharedKey);

    delete[] _receiveNonce;
    _receiveNonce = nullptr;

    _receiveNonce = new unsigned char[24];

    std::memcpy(_receiveNonce, decrypted.data() + 24, 24);

    clearLength = static_cast<int>(decrypted.size() - 48);

    unsigned char* result = new unsigned char[clearLength];

    if (clearLength > 0) {
        std::memcpy(result, decrypted.data() + 48, clearLength);
    }

    _pepperState = 4;

    return result;
}

unsigned char* Messaging::SendPepperLoginResponse(const unsigned char* bodyPayload, int bodyLength, int& outputLength) {
    outputLength = 0;

    const int plaintextLength = 24 + 32 + bodyLength;

    std::vector<unsigned char> plaintext(plaintextLength);

    std::memcpy(plaintext.data(), _sendNonce, 24);
    std::memcpy(plaintext.data() + 24, _secretKey, 32);

    if (bodyLength > 0) {
        std::memcpy(plaintext.data() + 56, bodyPayload, bodyLength);
    }

    Blake2BHasher hasher;

    hasher.Update(_receiveNonce, 0, 24);
    hasher.Update(_clientPublicKey, 0, 32);
    hasher.Update(PepperKey::SERVER_PK.data(), 0, PepperKey::SERVER_PK.size());

    size_t hashLength = 0;

    unsigned char* hash = hasher.Finish(hashLength);

    unsigned char nonce[24];

    std::memcpy(nonce, hash, 24);

    delete[] hash;

    bytearray encryptedBytes = TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet(bytearray(plaintext.begin(), plaintext.end()), bytearray(nonce, nonce + 24), _sharedKey);

    outputLength = static_cast<int>(encryptedBytes.size());

    unsigned char* result = new unsigned char[outputLength];

    std::memcpy(result, encryptedBytes.data(), outputLength);

    PepperEncrypter* newDecrypter = new PepperEncrypter(_secretKey, _receiveNonce);
    PepperEncrypter* newEncrypter = new PepperEncrypter(_secretKey, _sendNonce);

    delete _decrypter;
    delete _encrypter;

    _decrypter = newDecrypter;
    _encrypter = newEncrypter;

    _pepperState = 5;

    return result;
}

void Messaging::ReadHeader(const unsigned char* buffer, int& messageType, int& encodingLength, short& messageVersion) {
    ByteStream stream(buffer, HeaderSize);

    messageType = stream.ReadShort();
    encodingLength = stream.ReadInt24();
    messageVersion = stream.ReadShort();
}

void Messaging::WriteHeader(unsigned char* buffer, PiranhaMessage* message, int length) {
    ByteStream stream(buffer, HeaderSize);

    stream.WriteShort(static_cast<short>(message->GetMessageType()));
    stream.WriteInt24(length);
    stream.WriteShort(message->GetMessageVersion());
}

Messaging::~Messaging() {
    delete _factory;
    delete _encrypter;
    delete _decrypter;

    delete[] _clientPublicKey;
    delete[] _sendNonce;
    delete[] _receiveNonce;
    delete[] _secretKey;

    delete _manager;
}