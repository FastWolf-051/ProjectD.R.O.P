#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class HomeReadGenericStorageReqMessage : public PiranhaMessage {
public:
    void Decode() override {
        PiranhaMessage::Decode();
    }

    int GetMessageType() override {
        return 16845;
    }
};