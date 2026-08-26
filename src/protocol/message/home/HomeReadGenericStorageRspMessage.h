#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class HomeReadGenericStorageRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteVInt(1);
        _stream->WriteByte(96);
        _stream->WriteString("PreBattleCacheData");

        _stream->WriteVInt(2);
        _stream->WriteByte(96);
        _stream->WriteString("{}");

        _stream->WriteVInt(-1); // struture terminator flag
    }

    int GetMessageType() override {
        return 23570;
    }
};