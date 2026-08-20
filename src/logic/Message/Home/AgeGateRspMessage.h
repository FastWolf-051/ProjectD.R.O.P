#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class AgeGateRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();
    }

    int GetMessageType() override {
        return 20343;
    }
};