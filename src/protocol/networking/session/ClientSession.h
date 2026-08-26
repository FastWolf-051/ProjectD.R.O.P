#pragma once

#include <asio.hpp>

#include "../../../shared/base/PiranhaMessage.h"

class Messaging;

class ClientSession {
private:
    static const int receiveBufferCapacity = 16384;

    asio::ip::tcp::socket _socket;
    Messaging* _messaging;

    unsigned char* _receiveBuffer;

public:
    explicit ClientSession(asio::ip::tcp::socket socket);
    ~ClientSession();

    void Run();
    void Send(unsigned char* buffer, int size);

    void SendMessage(PiranhaMessage* message);
};