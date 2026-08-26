#include "LogicLong.h"

#include "../../protocol/datastream/ByteStream.h"
#include "../../protocol/datastream/ChecksumEncoder.h"

void LogicLong::Decode(ByteStream* stream) {
    _highInteger = stream->ReadInt();
    _lowInteger = stream->ReadInt();
}

void LogicLong::Encode(ChecksumEncoder* stream) {
    stream->WriteInt(_highInteger);
    stream->WriteInt(_lowInteger);
}