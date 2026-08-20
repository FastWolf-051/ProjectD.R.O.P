#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class KeepAliveServerMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteHexa("91-bc-97-92-83-68"); // server tick may be
    }

    int GetMessageType() override {
        return 20108;
    }
};