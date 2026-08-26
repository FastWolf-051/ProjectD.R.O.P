#pragma once

#include "../../../logic/math/LogicLong.h"
#include "../../../logic/helper/ByteStreamHelper.h"

#include "../../../shared/base/PiranhaMessage.h"

#include <cstdio>
#include <cstring>

class LoginMessage : public PiranhaMessage {
private:
    LogicLong _accountId;

    char* _passToken = nullptr;

    int _clientMajor;
    int _clientMinor;
    int _clientBuild;

    char* _traceId = nullptr;
    char* _deviceInfo = nullptr;
    char* _osVersion = nullptr;
    char* _spanId = nullptr;

    bool _isAndroid;

    int _preferredLanguage;

public:
    void Decode() override {
        PiranhaMessage::Decode();

        _accountId = ByteStreamHelper::DecodeLogicLong(*_stream);

        delete[] _passToken;
        _passToken = _stream->ReadString();

        _clientMajor = _stream->ReadVInt();
        _clientMinor = _stream->ReadVInt();
        _clientBuild = _stream->ReadVInt();

        _stream->ReadVInt();
        _stream->ReadVInt();

        delete[] _traceId;
        _traceId = _stream->ReadString();

        _stream->ReadString();
        _stream->ReadString();
        _stream->ReadString();

        delete[] _deviceInfo;
        _deviceInfo = _stream->ReadString();

        _stream->ReadString();

        delete[] _osVersion;
        _osVersion = _stream->ReadString();

        _isAndroid = _stream->ReadBoolean();

        _stream->ReadStringReference();

        delete[] _spanId;
        _spanId = _stream->ReadStringReference();

        _stream->ReadStringReference();

        _preferredLanguage = ByteStreamHelper::ReadDataReference(*_stream);

        _stream->ReadStringReference();

        _stream->ReadBoolean();
        _stream->ReadBoolean();

        _stream->ReadString();

        _stream->ReadVInt();

        _stream->ReadStringReference();
        _stream->ReadStringReference();
        _stream->ReadStringReference();
        _stream->ReadStringReference();

        _stream->ReadVInt();
        _stream->ReadVInt();
    }

    int GetMessageType() override {
        return 10101;
    }

    const LogicLong& GetAccountId() const {
        return _accountId;
    }

    char* GetPassToken() {
        return _passToken;
    }

    int GetClientMajor() const {
        return _clientMajor;
    }

    int GetClientMinor() const {
        return _clientMinor;
    }

    int GetClientBuild() const {
        return _clientBuild;
    }

    char* GetClientVersion() {
        char* version = new char[32];

        std::snprintf(version, 32, "%d.%d.%d", _clientMajor, _clientMinor, _clientBuild);

        return version;
    }

    char* GetTraceId() {
        return _traceId;
    }

    char* GetSpanId() {
        return _spanId;
    }

    char* GetDeviceInfo() {
        return _deviceInfo;
    }

    char* GetOsVersion() {
        return _osVersion;
    }

    bool IsAndroid() const {
        return _isAndroid;
    }

    int GetPreferredLanguage() const {
        return _preferredLanguage;
    }

    ~LoginMessage() override {
        delete[] _passToken;
        delete[] _traceId;
        delete[] _deviceInfo;
        delete[] _osVersion;
        delete[] _spanId;
    }

};