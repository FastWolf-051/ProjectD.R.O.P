#pragma once

#include "../../../shared/base/PiranhaMessage.h"

class HomeServerSettingRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        SetMessageIndex(1);
        
        PiranhaMessage::Encode();
        
        _stream->WriteHexa("01-83-a0-b8-02-02-82-88-4e-1c-a0-00-00-00-0b-01-01-11-00-02-11-00-03-81-01-7f-1d-11-00-7f");
    }

    int GetMessageType() override {
        return 25591;
    }
};