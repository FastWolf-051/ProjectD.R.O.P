#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class LeaderboardGetCurrentRankReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 14123;
    }
};