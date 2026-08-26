#pragma once

#include "../logic/factory/LogicSlashMessageFactory.h"

#include "pepper/keys/PepperKeys.h"
#include "pepper/PepperEncrypter.h"

#include "../shared/base/PiranhaMessage.h"

class ClientSession;
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

    ClientSession* _connection;
    MessageManager* _manager;

public:
    explicit Messaging(ClientSession* connection);
    ~Messaging();

    int OnReceive(unsigned char* buffer, int size);
    void Send(PiranhaMessage* message);

private:
    unsigned char* DecodePepperLogin(const unsigned char* payload, int payloadLength, int& clearLength);
    unsigned char* EncodePepperLoginResponse(const unsigned char* bodyPayload, int bodyLength, int& outputLength);

    void PrepareToEncodeData(PiranhaMessage* message);

    static void ReadDataHeader(const unsigned char* buffer, int& messageType, int& encodingLength, short& messageVersion);
    static void WriteDataHeader(unsigned char* buffer, PiranhaMessage* message, int length);
};