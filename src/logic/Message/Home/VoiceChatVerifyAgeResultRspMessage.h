#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class VoiceChatVerifyAgeResultRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteTaggedVInt(1, 0);

        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 27284;
    }
};