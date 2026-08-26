#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class MatchMakeStartRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();
    }

    int GetMessageType() override {
        return 26681;
    }
};