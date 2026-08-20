#pragma once

#include "../DataStream/ByteStream.h"

class PiranhaMessage {
protected:
    ByteStream* _stream;
    short _version;

public:
    PiranhaMessage(short messageVersion = 0) {
        _stream = new ByteStream(10);
        _version = messageVersion;
    }

    virtual ~PiranhaMessage() {
        delete _stream;
    }

    virtual void Decode() {
        _stream->ReadVInt();
        _stream->ReadVInt();
        _stream->ReadVInt(); // string list ptr
    }

    virtual void Encode() {
        _stream->WriteVInt(0);
        _stream->WriteVInt(0);
        _stream->WriteVInt(0); // empty string list
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
};