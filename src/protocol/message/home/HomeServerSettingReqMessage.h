#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class HomeServerSettingReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 11500;
    }
};