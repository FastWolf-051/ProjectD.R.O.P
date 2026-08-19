#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class VoiceChatVerifyAgeResultReqMessage : public PiranhaMessage {
private:
    std::string _age;
public:
    void Decode() override {
        PiranhaMessage::Decode();

        _stream->ReadVInt(); // 1
        _stream->ReadByte(); // 96
        _age = _stream->ReadString();

        _stream->ReadVInt(); // will be -1
    }

    int GetMessageType() override {
        return 12727;
    }

    const char* GetAge() {
        return _age.c_str();
    }
};