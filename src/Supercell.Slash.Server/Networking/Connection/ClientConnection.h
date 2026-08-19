#pragma once

#include <asio.hpp>

#include "../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class Messaging;

class ClientConnection {
private:
    static const int ReceiveBufferSize = 16384;

    asio::ip::tcp::socket _socket;
    Messaging* _messaging;

    unsigned char* _receiveBuffer;

public:
    explicit ClientConnection(asio::ip::tcp::socket socket);
    ~ClientConnection();

    void Run();
    void Send(unsigned char* buffer, int size);

    void SendMessage(PiranhaMessage* message);

    asio::ip::tcp::socket& GetSocket();
};