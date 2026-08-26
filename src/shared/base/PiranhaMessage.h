#pragma once

#include "../../protocol/datastream/ByteStream.h"

class PiranhaMessage {
protected:
    ByteStream* _stream;
    short _version;
private:
    int _messageIndex;
public:
    PiranhaMessage(short messageVersion = 0) {
        _stream = new ByteStream(10);
        _version = messageVersion;
        _messageIndex = 0;
    }

    virtual ~PiranhaMessage() {
        delete _stream;
    }

    virtual void Decode() {
        _messageIndex = _stream->ReadVInt();
        _stream->ReadVInt();
        _stream->ReadVInt(); // string list ptr
    }

    virtual void Encode() {
        _stream->WriteVInt(_messageIndex);
        _stream->WriteVInt(0);
        _stream->WriteVInt(9); // KVP array of strings
        {
            _stream->WriteString("client.account_id");
            _stream->WriteString("54");

            _stream->WriteString("client.country");
            _stream->WriteString("DE");

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
    }

    virtual int GetMessageType() {
        return 0;
    }

    virtual int GetServiceNodeType() {
        return -1;
    }

    short GetMessageVersion() {
        return _version;
    }

    void SetMessageVersion(short version) {
        _version = version;
    }

    bool IsServerToClientMessage() {
        return GetMessageType() >= 20000;
    }

    unsigned char* GetMessageBytes() {
        return _stream->GetByteArray();
    }

    int GetEncodingLength() {
        return _stream->GetLength();
    }

    ByteStream* GetByteStream() {
        return _stream;
    }

    void SetMessageIndex(int index) {
        _messageIndex = index;
    }

    int GetMessageIndex() {
        return _messageIndex;
    }
};