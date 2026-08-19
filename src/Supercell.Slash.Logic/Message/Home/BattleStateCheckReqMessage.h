#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class BattleStateCheckReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 15998;
    }
};