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

    bool _loggedIn;
    int _accountId;

    char* _loginCountry;
    char* _device;
    char* _deviceId;
    char* _clientVersion;
    char* _spanId;
    char* _traceId;

public:
    explicit ClientSession(asio::ip::tcp::socket socket);
    ~ClientSession();

    void Run();
    void Send(unsigned char* buffer, int size);
    void SendMessage(PiranhaMessage* message);

    void SetLoggedIn(bool flag);
    bool IsLoggedIn();

    int GetAccountId() const;

    const char* GetLoginCountry() const;
    const char* GetDevice() const;
    const char* GetDeviceId() const;
    const char* GetClientVersion() const;
    const char* GetSpanId() const;
    const char* GetTraceId() const;
    const char* GetIp() const;

    void SetAccountId(int value);
    void SetLoginCountry(const char* value);
    void SetDevice(const char* value);
    void SetDeviceId(const char* value);
    void SetClientVersion(const char* value);
    void SetSpanId(const char* value);
    void SetTraceId(const char* value);
};