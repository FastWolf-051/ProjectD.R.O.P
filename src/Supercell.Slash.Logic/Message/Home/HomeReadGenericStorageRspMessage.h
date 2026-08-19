#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class HomeReadGenericStorageRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        // PiranhaMessage::Encode();
        _stream->WriteVInt(19);
        _stream->WriteVInt(0);
        
        _stream->WriteVInt(9); // KVP array of strings
        {
            _stream->WriteString("client.account_id");
            _stream->WriteString("16950");

            _stream->WriteString("client.country");
            _stream->WriteString("BZ");

            _stream->WriteString("client.device");
            _stream->WriteString("ANDROID_DEVICE");

            _stream->WriteString("client.device_id");
            _stream->WriteString("XVRT00WQ7");

            _stream->WriteString("client.ip");
            _stream->WriteString("0.0.0.0");

            _stream->WriteString("client.version");
            _stream->WriteString("0.3.296710");

            _stream->WriteString("sampled");
            _stream->WriteString("false");

            _stream->WriteString("span-id");
            _stream->WriteString("2002a9003e000800");

            _stream->WriteString("trace-id");
            _stream->WriteString("99899f768c54c621437e270bd0000fe3c");
        }

        _stream->WriteVInt(1);
        _stream->WriteByte(96);
        _stream->WriteString("PreBattleCacheData");

        _stream->WriteVInt(2);
        _stream->WriteByte(96);
        _stream->WriteString("{}");

        _stream->WriteVInt(-1); // struture terminator flag
    }

    int GetMessageType() override {
        return 23570;
    }
};