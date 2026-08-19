#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class KeepAliveMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 10108;
    }
};