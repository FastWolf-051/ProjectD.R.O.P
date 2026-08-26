#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class QuestGetDataReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 13925;
    }
};