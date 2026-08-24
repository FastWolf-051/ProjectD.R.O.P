#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class LeaderboardInfoReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 15332;
    }
};