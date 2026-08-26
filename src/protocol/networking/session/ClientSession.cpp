#include "ClientSession.h"

#include "../../Messaging.h"

#include "../../../shared/utils/debug/Debugger.h"

#include <cstring>
#include <utility>

ClientSession::ClientSession(asio::ip::tcp::socket socket) : _socket(std::move(socket)) {
    _receiveBuffer = new unsigned char[receiveBufferCapacity];
    _messaging = new Messaging(this);
}

void ClientSession::Run() {
    int receiveBufferIndex = 0;

    while (_socket.is_open()) {
        asio::error_code error;

        std::size_t read = _socket.read_some(asio::buffer(
            _receiveBuffer + receiveBufferIndex,
            receiveBufferCapacity - receiveBufferIndex
        ), error);

        if (error) {
            if (error == asio::error::eof) break;

            Debugger::Error("Receive failed: %s", error.message().c_str());

            break;
        }

        if (read == 0) break;

        receiveBufferIndex += static_cast<int>(read);

        int consumed = _messaging->OnReceive(_receiveBuffer, receiveBufferIndex);

        if (consumed < 0) break;

        if (consumed > 0) {
            std::memmove(_receiveBuffer, _receiveBuffer + consumed, receiveBufferIndex - consumed);

            receiveBufferIndex -= consumed;
        }

        if (receiveBufferIndex >= receiveBufferCapacity) {
            Debugger::Error("[ClientSession]: got receive buffer overflow");

            break;
        }
    }
}

void ClientSession::Send(unsigned char* buffer, int size) {
    asio::error_code error;

    asio::write(_socket, asio::buffer(buffer, size), error);

    if (error) {
        Debugger::Error("Failed to send data: %s", error.message().c_str());
    }
}

void ClientSession::SendMessage(PiranhaMessage* message) {
    if (message == nullptr) return;

    _messaging->Send(message);
}

ClientSession::~ClientSession() {
    delete _messaging;

    delete[] _receiveBuffer;
}