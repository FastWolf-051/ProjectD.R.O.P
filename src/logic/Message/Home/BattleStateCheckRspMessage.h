#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class BattleStateCheckRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        _stream->WriteVInt(2);
        _stream->WriteVInt(0);
        _stream->WriteVInt(0);

        ByteStreamHelper::WriteTaggedBoolean(*_stream, 1, false);
        ByteStreamHelper::WriteTaggedBoolean(*_stream, 2, false);

        _stream->WriteTaggedVInt(3, 0);

        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 21758;
    }
};