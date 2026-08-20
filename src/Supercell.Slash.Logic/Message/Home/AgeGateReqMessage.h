#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class AgeGateReqMessage : public PiranhaMessage {
private:
    int _age;
public:
    void Decode() override {
        PiranhaMessage::Decode();

        _age = _stream->ReadTaggedVInt();

        _stream->ReadVInt(); // will be -1 cus this is acts like packet tarminator state
    }

    int GetMessageType() override {
        return 16666;
    }

    int GetAge() {
        return _age;
    }
};