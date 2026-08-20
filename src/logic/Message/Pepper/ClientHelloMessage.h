#pragma once

#include "../../../titan/Message/PiranhaMessage.h"
#include <string>

class ClientHelloMessage : public PiranhaMessage {
private:
    int _protocol;      // encryption used (< 3 is pepper)
    int _keyVersion;
    int _majorVersion;
    int _minorVersion;
    int _build;

    std::string _contentHash;

    int _deviceType;
    int _appStore;

public:
    void Decode() override {
        PiranhaMessage::Decode();

        _protocol = _stream->ReadInt();
        _keyVersion = _stream->ReadInt();
        _majorVersion = _stream->ReadInt();
        _minorVersion = _stream->ReadInt();
        _build = _stream->ReadInt();

        _contentHash = _stream->ReadStringReference(900000);

        _deviceType = _stream->ReadInt();
        _appStore = _stream->ReadInt();
    }

    int GetMessageType() override {
        return 10100;
    }

    int GetProtocol() const {
        return _protocol;
    }

    int GetKeyVersion() const {
        return _keyVersion;
    }

    int GetMajorVersion() const {
        return _majorVersion;
    }

    int GetMinorVersion() const {
        return _minorVersion;
    }

    int GetBuild() const {
        return _build;
    }

    const std::string& GetContentHash() const {
        return _contentHash;
    }

    int GetDeviceType() const {
        return _deviceType;
    }

    int GetAppStore() const {
        return _appStore;
    }
};