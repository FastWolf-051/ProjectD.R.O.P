#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class ChatAccountBanStatusMessage : public PiranhaMessage {
private:
    bool _isBanned = false;
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteBoolean(_isBanned);
    }

    int GetMessageType() override {
        return 27276;
    }
};