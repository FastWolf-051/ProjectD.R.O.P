#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class KeepAliveMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 10108;
    }
};