#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class ClientCryptoErrorMessage : public PiranhaMessage {
private:
    int _corruptedMessageType;
public:
    void Decode() override {
        PiranhaMessage::Decode();

        _corruptedMessageType = _stream->ReadInt();
    }

    int GetMessageType() override {
        return 10099;
    }

    int GetCorrputedMessageType() {
        return _corruptedMessageType;
    }
};