#pragma once

#include "../../logic/Factory/LogicSlashMessageFactory.h"

#include "../Privacy/PepperKeys.h"

#include "../../titan/Encryption/Pepper/PepperEncrypter.h"
#include "../../titan/Message/PiranhaMessage.h"

class ClientConnection;
class MessageManager;

class Messaging {
private:
    static const int HeaderSize = 7;

    LogicSlashMessageFactory* _factory;

    PepperEncrypter* _encrypter;
    PepperEncrypter* _decrypter;

    int _pepperState;

    unsigned char* _clientPublicKey;
    unsigned char* _sendNonce;
    unsigned char* _receiveNonce;
    std::vector<unsigned char>  _sharedKey;
    unsigned char* _secretKey;

    ClientConnection* _connection;
    MessageManager* _manager;

    int _handledMessagesCount;

public:
    explicit Messaging(ClientConnection* connection);
    ~Messaging();

    int OnReceive(unsigned char* buffer, int size);
    void Send(PiranhaMessage* message);

private:
    unsigned char* HandlePepperLogin(
        const unsigned char* payload,
        int payloadLength,
        int& clearLength
    );

    unsigned char* SendPepperLoginResponse(
        const unsigned char* bodyPayload,
        int bodyLength,
        int& outputLength
    );

    static void ReadHeader(
        const unsigned char* buffer,
        int& messageType,
        int& encodingLength,
        short& messageVersion
    );

    static void WriteHeader(
        unsigned char* buffer,
        PiranhaMessage* message,
        int length
    );
};