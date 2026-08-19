#include "LogicLong.h"

#include "../DataStream/ByteStream.h"
#include "../DataStream/ChecksumEncoder.h"

void LogicLong::Decode(ByteStream* stream) {
    _highInteger = stream->ReadInt();
    _lowInteger = stream->ReadInt();
}

void LogicLong::Encode(ChecksumEncoder* stream) {
    stream->WriteInt(_highInteger);
    stream->WriteInt(_lowInteger);
}