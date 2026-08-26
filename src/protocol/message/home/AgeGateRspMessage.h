#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class AgeGateRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();
    }

    int GetMessageType() override {
        return 20343;
    }
};