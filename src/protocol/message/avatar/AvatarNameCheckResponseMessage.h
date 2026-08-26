#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class AvatarNameCheckResponseMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteVInt(0);

        _stream->WriteBoolean(false);

        _stream->WriteString("");
    }

    int GetMessageType() override {
        return 28946;
    }
};