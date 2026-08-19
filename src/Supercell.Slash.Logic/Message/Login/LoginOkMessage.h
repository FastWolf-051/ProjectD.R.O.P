#pragma once

#include <cstdint>
#include <vector>

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"
#include "../../Helper/ByteStreamHelper.h"
#include "../../../Supercell.Slash.Titan/Logic/LogicLong.h"

class LoginOkMessage : public PiranhaMessage {
private:
    LogicLong _accountId;
    LogicLong _avatarId;

    const char* _passToken = "";

    int _serverMajorVersion;
    int _serverMinor;
    int _serverContentVersion;

    const char* _serverEnvironment = "";

    int _sessionCount;
    int _playTimeSeconds;
    int _daysSinceStartedPlaying;

    const char* _serverTime = "";
    const char* _accountCreatedDate = "";

    int _startupCooldownSeconds;

    const char* _googleServiceId = "";
    const char* _loginCountry = "";
    const char* _kunlunId = "";

    std::vector<const char*> _contentURLlist;
    std::vector<const char*> _chronosContentURLlist;

    std::vector<uint8_t> _accountTokenReference;

    const char* _sessionId = "";

    const char* _helpshiftAuthToken = nullptr;
    const char* _helpshiftAppId = nullptr;
    const char* _helpshiftDomain = nullptr;
    const char* _helpshiftApiKey = nullptr;

public:
    void Encode() override {
        PiranhaMessage::Encode();

        ByteStreamHelper::EncodeLogicLong(*_stream, _accountId);
        ByteStreamHelper::EncodeLogicLong(*_stream, _avatarId);

        _stream->WriteString(_passToken);
        _stream->WriteString("");
        _stream->WriteString("");

        _stream->WriteVInt(_serverMajorVersion);
        _stream->WriteVInt(_serverMinor);
        _stream->WriteVInt(_serverContentVersion);
        _stream->WriteVInt(0);

        _stream->WriteString(_serverEnvironment);

        _stream->WriteVInt(_sessionCount);
        _stream->WriteVInt(_playTimeSeconds);
        _stream->WriteVInt(_daysSinceStartedPlaying);

        _stream->WriteString("");
        _stream->WriteString(_serverTime);
        _stream->WriteString(_accountCreatedDate);

        _stream->WriteVInt(_startupCooldownSeconds);

        _stream->WriteString(_googleServiceId);
        _stream->WriteString(_loginCountry);
        _stream->WriteString(_kunlunId);
        _stream->WriteString("");
        _stream->WriteString("");
        _stream->WriteString("");

        _stream->WriteVInt(0);
        _stream->WriteVInt(0);
        _stream->WriteVInt(0);

        if (!_contentURLlist.empty()) {
            _stream->WriteVInt(static_cast<int>(_contentURLlist.size()));

            for (const char* url : _contentURLlist) {
                _stream->WriteString(url);
            }
        }
        else {
            _stream->WriteVInt(-1);
        }

        if (!_chronosContentURLlist.empty()) {
            _stream->WriteVInt(static_cast<int>(_chronosContentURLlist.size()));

            for (const char* url : _chronosContentURLlist) {
                _stream->WriteString(url);
            }
        }
        else {
            _stream->WriteVInt(-1);
        }

        if (!_accountTokenReference.empty()) {
            _stream->WriteBytes(_accountTokenReference.data(), _accountTokenReference.size());
        }
        else {
            _stream->WriteBytes(nullptr, 0);
        }

        _stream->WriteBoolean(false);
        _stream->WriteBoolean(false);
        _stream->WriteBoolean(false);

        _stream->WriteVInt(0);
        _stream->WriteVInt(2118);

        _stream->WriteStringReference(_sessionId);

        _stream->WriteBoolean(_helpshiftAuthToken != nullptr);
        if (_helpshiftAuthToken != nullptr) {
            _stream->WriteStringReference(_helpshiftAuthToken);
        }

        _stream->WriteBoolean(_helpshiftAppId != nullptr);
        if (_helpshiftAppId != nullptr) {
            _stream->WriteStringReference(_helpshiftAppId);
        }

        _stream->WriteBoolean(_helpshiftDomain != nullptr);
        if (_helpshiftDomain != nullptr) {
            _stream->WriteStringReference(_helpshiftDomain);
        }

        _stream->WriteBoolean(_helpshiftApiKey != nullptr);
        if (_helpshiftApiKey != nullptr) {
            _stream->WriteStringReference(_helpshiftApiKey);
        }
    }

    int GetMessageType() override {
        return 20375;
    }

    void SetAccountId(const LogicLong& value) {
        _accountId = value;
    }

    void SetAvatarId(const LogicLong& value) {
        _avatarId = value;
    }

    void SetPassToken(const char* value) {
        _passToken = value;
    }

    void SetServerMajorVersion(int value) {
        _serverMajorVersion = value;
    }

    void SetServerMinor(int value) {
        _serverMinor = value;
    }

    void SetServerContentVersion(int value) {
        _serverContentVersion = value;
    }

    void SetServerVersion(int major, int minor, int content) {
        _serverMajorVersion = major;
        _serverMinor = minor;
        _serverContentVersion = content;
    }

    void SetServerEnvironment(const char* value) {
        _serverEnvironment = value;
    }

    void SetSessionCount(int value) {
        _sessionCount = value;
    }

    void SetPlayTimeSeconds(int value) {
        _playTimeSeconds = value;
    }

    void SetDaysSinceStartedPlaying(int value) {
        _daysSinceStartedPlaying = value;
    }

    void SetServerTime(const char* value) {
        _serverTime = value;
    }

    void SetAccountCreatedDate(const char* value) {
        _accountCreatedDate = value;
    }

    void SetStartupCooldownSeconds(int value) {
        _startupCooldownSeconds = value;
    }

    void SetGoogleServiceId(const char* value) {
        _googleServiceId = value;
    }

    void SetLoginCountry(const char* value) {
        _loginCountry = value;
    }

    void SetKunlunId(const char* value) {
        _kunlunId = value;
    }

    void SetContentURLlist(const std::vector<const char*>& value) {
        _contentURLlist = value;
    }

    void SetChronosContentURLlist(const std::vector<const char*>& value) {
        _chronosContentURLlist = value;
    }

    void SetAccountTokenReference(const std::vector<uint8_t>& value) {
        _accountTokenReference = value;
    }

    void SetSessionId(const char* value) {
        _sessionId = value;
    }

    void SetHelpshiftAuthToken(const char* value) {
        _helpshiftAuthToken = value;
    }

    void SetHelpshiftAppId(const char* value) {
        _helpshiftAppId = value;
    }

    void SetHelpshiftDomain(const char* value) {
        _helpshiftDomain = value;
    }

    void SetHelpshiftApiKey(const char* value) {
        _helpshiftApiKey = value;
    }
};