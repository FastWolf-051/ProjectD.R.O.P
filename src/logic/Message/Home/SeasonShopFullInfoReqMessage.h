#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class SeasonShopFullInfoReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 18666;
    }
};