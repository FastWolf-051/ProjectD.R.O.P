#pragma once

#include "../../protocol/datastream/ByteStream.h"

class PiranhaMessage {
protected:
    ByteStream* _stream;
    short _version;

    const char* _attributes[9][2];
    int _attributeCount;

private:
    int _messageIndex;

public:
    PiranhaMessage(short messageVersion = 0) {
        _stream = new ByteStream(10);
        _version = messageVersion;
        _messageIndex = 0;
        _attributeCount = 0;

        for (int i = 0; i < 9; ++i) {
            _attributes[i][0] = nullptr;
            _attributes[i][1] = nullptr;
        }
    }

    virtual ~PiranhaMessage() {
        delete _stream;
    }

    void AddAttribute(const char* key, const char* value) {
        if (_attributeCount >= 9)
            return;

        _attributes[_attributeCount][0] = key;
        _attributes[_attributeCount][1] = value;

        ++_attributeCount;
    }

    virtual void Decode() {
        _messageIndex = _stream->ReadVInt();
        _stream->ReadVInt();
        _stream->ReadVInt();
    }

    virtual void Encode() {
        _stream->WriteVInt(_messageIndex);
        _stream->WriteVInt(0);
        _stream->WriteVInt(_attributeCount);

        for (int i = 0; i < _attributeCount; ++i) {
            _stream->WriteString(_attributes[i][0]);
            _stream->WriteString(_attributes[i][1]);
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