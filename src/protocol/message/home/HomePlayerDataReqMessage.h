#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class HomePlayerDataReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 18867;
    }
};