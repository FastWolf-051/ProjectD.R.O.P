#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class MatchMakeStateNotifyMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteHexa("04-11-01-05-81-00-7f");
    }

    int GetMessageType() override {
        return 29084;
    }
};