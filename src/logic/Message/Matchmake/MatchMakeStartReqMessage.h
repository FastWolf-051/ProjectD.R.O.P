#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class MatchMakeStartReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 19228;
    }
};