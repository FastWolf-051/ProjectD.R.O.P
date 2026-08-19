#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class AgeGateReqMessage : public PiranhaMessage {
private:
    int _age;
public:
    void Decode() override {
        PiranhaMessage::Decode();

        _age = _stream->ReadTaggedVInt();

        _stream->ReadVInt(); // will be -1 cuz this is acts like packet terminator state
    }

    int GetMessageType() override {
        return 16666;
    }

    int GetAge() {
        return _age;
    }
};
