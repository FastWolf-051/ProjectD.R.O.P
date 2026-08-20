#pragma once

#include "../../../Supercell.Slash.Titan/Logic/LogicLong.h"
#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"
#include "../../Helper/ByteStreamHelper.h"

#include <string>

class LoginMessage : public PiranhaMessage {
private:
    LogicLong _accountId;

    std::string _passToken;

    int _clientMajor;
    int _clientMinor;
    int _clientBuild;

    std::string _deviceInfo;
    std::string _osVersion;

    bool _isAndroid;

    int _preferredLanguage;

public:
    void Decode() override {
        PiranhaMessage::Decode();

        _accountId = ByteStreamHelper::DecodeLogicLong(*_stream);

        char* passToken = _stream->ReadString();

        if (passToken != nullptr)
        {
            _passToken = passToken;
            delete[] passToken;
        }

        _clientMajor = _stream->ReadVInt();
        _clientMinor = _stream->ReadVInt();
        _clientBuild = _stream->ReadVInt();

        _stream->ReadVInt();
        _stream->ReadVInt();

        _stream->ReadString();
        _stream->ReadString();
        _stream->ReadString();
        _stream->ReadString();

        _deviceInfo = _stream->ReadString();

        _stream->ReadString();

        _osVersion = _stream->ReadString();

        _isAndroid = _stream->ReadBoolean();

        _stream->ReadStringReference();
        _stream->ReadStringReference();
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

    const std::string& GetPassToken() const {
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

    const std::string& GetDeviceInfo() const {
        return _deviceInfo;
    }

    const std::string& GetOsVersion() const {
        return _osVersion;
    }

    bool GetIsAndroid() const {
        return _isAndroid;
    }

    int GetPreferredLanguage() const {
        return _preferredLanguage;
    }

    std::string GetClientVersion() const {
        char buffer[32];

        std::snprintf(buffer, sizeof(buffer), "%d.%d.%d",
            _clientMajor, _clientMinor, _clientBuild
        );

        return std::string(buffer);
    }
};