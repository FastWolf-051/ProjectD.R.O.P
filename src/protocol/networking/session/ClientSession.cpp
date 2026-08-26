#include "ClientSession.h"

#include "../../Messaging.h"

#include "../../../shared/utils/debug/Debugger.h"

#include <cstring>
#include <string>
#include <utility>

ClientSession::ClientSession(asio::ip::tcp::socket socket)
    : _socket(std::move(socket)) {

    _receiveBuffer = new unsigned char[receiveBufferCapacity];
    _messaging = new Messaging(this);

    _loggedIn = false;
    _accountId = 0;

    _loginCountry = nullptr;
    _device = nullptr;
    _deviceId = nullptr;
    _clientVersion = nullptr;
    _spanId = nullptr;
    _traceId = nullptr;
}

void ClientSession::Run() {
    int receiveBufferIndex = 0;

    while (_socket.is_open()) {
        asio::error_code error;

        std::size_t read = _socket.read_some(
            asio::buffer(
                _receiveBuffer + receiveBufferIndex,
                receiveBufferCapacity - receiveBufferIndex
            ),
            error
        );

        if (error) {
            if (error == asio::error::eof)
                break;

            Debugger::Error(
                "Receive failed: %s",
                error.message().c_str()
            );

            break;
        }

        if (read == 0)
            break;

        receiveBufferIndex += static_cast<int>(read);

        int consumed = _messaging->OnReceive(
            _receiveBuffer,
            receiveBufferIndex
        );

        if (consumed < 0)
            break;

        if (consumed > 0) {
            std::memmove(
                _receiveBuffer,
                _receiveBuffer + consumed,
                receiveBufferIndex - consumed
            );

            receiveBufferIndex -= consumed;
        }

        if (receiveBufferIndex >= receiveBufferCapacity) {
            Debugger::Error(
                "[ClientSession]: got receive buffer overflow"
            );

            break;
        }
    }
}

void ClientSession::Send(unsigned char* buffer, int size) {
    asio::error_code error;

    asio::write(
        _socket,
        asio::buffer(buffer, size),
        error
    );

    if (error) {
        Debugger::Error(
            "Failed to send data: %s",
            error.message().c_str()
        );
    }
}

void ClientSession::SendMessage(PiranhaMessage* message) {
    if (message == nullptr)
        return;

    _messaging->Send(message);
}

void ClientSession::SetLoggedIn(bool flag) {
    _loggedIn = flag;
}

bool ClientSession::IsLoggedIn() {
    return _loggedIn;
}

void ClientSession::SetAccountId(int value) {
    _accountId = value;
}

int ClientSession::GetAccountId() const {
    return _accountId;
}

void ClientSession::SetLoginCountry(const char* value) {
    delete[] _loginCountry;

    if (value == nullptr) {
        _loginCountry = nullptr;
        return;
    }

    _loginCountry = new char[std::strlen(value) + 1];
    std::strcpy(_loginCountry, value);
}

void ClientSession::SetDevice(const char* value) {
    delete[] _device;

    if (value == nullptr) {
        _device = nullptr;
        return;
    }

    _device = new char[std::strlen(value) + 1];
    std::strcpy(_device, value);
}

void ClientSession::SetDeviceId(const char* value) {
    delete[] _deviceId;

    if (value == nullptr) {
        _deviceId = nullptr;
        return;
    }

    _deviceId = new char[std::strlen(value) + 1];
    std::strcpy(_deviceId, value);
}

void ClientSession::SetClientVersion(const char* value) {
    delete[] _clientVersion;

    if (value == nullptr) {
        _clientVersion = nullptr;
        return;
    }

    _clientVersion = new char[std::strlen(value) + 1];
    std::strcpy(_clientVersion, value);
}

void ClientSession::SetSpanId(const char* value) {
    delete[] _spanId;

    if (value == nullptr) {
        _spanId = nullptr;
        return;
    }

    _spanId = new char[std::strlen(value) + 1];
    std::strcpy(_spanId, value);
}

void ClientSession::SetTraceId(const char* value) {
    delete[] _traceId;

    if (value == nullptr) {
        _traceId = nullptr;
        return;
    }

    _traceId = new char[std::strlen(value) + 1];
    std::strcpy(_traceId, value);
}

const char* ClientSession::GetLoginCountry() const {
    return _loginCountry;
}

const char* ClientSession::GetDevice() const {
    return _device;
}

const char* ClientSession::GetDeviceId() const {
    return _deviceId;
}

const char* ClientSession::GetClientVersion() const {
    return _clientVersion;
}

const char* ClientSession::GetSpanId() const {
    return _spanId;
}

const char* ClientSession::GetTraceId() const {
    return _traceId;
}

const char* ClientSession::GetIp() const {
    static thread_local std::string ip;

    ip = _socket.remote_endpoint().address().to_string();

    return ip.c_str();
}

ClientSession::~ClientSession() {
    delete _messaging;
    delete[] _receiveBuffer;

    delete[] _loginCountry;
    delete[] _device;
    delete[] _deviceId;
    delete[] _clientVersion;
    delete[] _spanId;
    delete[] _traceId;
}