#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class DSClusterReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 14731;
    }
};