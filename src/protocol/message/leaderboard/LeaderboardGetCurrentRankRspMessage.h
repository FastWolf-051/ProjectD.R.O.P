#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class LeaderboardGetCurrentRankRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteTaggedVInt(1, 391); // rank

        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 22806;
    }
};