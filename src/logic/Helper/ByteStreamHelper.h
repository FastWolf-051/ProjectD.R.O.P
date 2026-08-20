#pragma once

#include <cstdint>

#include "../../titan/DataStream/ByteStream.h"
#include "../Data/Core/GlobalID.h"
#include "../../titan/Logic/LogicLong.h"

class ByteStreamHelper {
public:
    static void WriteDataReference(ByteStream& stream, int type, int id) {
        if (type <= 0) {
            stream.WriteVInt(0);
            return;
        }

        stream.WriteVInt(type);
        stream.WriteVInt(id);
    }

    static void WriteDataReference(ByteStream& stream, int globalId) {
        if (globalId <= 0) {
            stream.WriteVInt(0);
            return;
        }

        stream.WriteVInt(GlobalID::GetClassID(globalId));
        stream.WriteVInt(GlobalID::GetInstanceID(globalId));
    }

    static int ReadDataReference(ByteStream& stream) {
        int type = stream.ReadVInt();

        if (type <= 0) return 0;

        int id = stream.ReadVInt();

        return GlobalID::CreateGlobalID(type, id);
    }

    static void EncodeLogicLong(ByteStream& stream, const LogicLong& id) {
        stream.WriteInt(id.GetHigherInt());
        stream.WriteInt(id.GetLowerInt());
    }

    static LogicLong DecodeLogicLong(ByteStream& stream) {
        int high = stream.ReadInt();
        int low = stream.ReadInt();

        return LogicLong(high, low);
    }

    // Project R.I.S.E specific
    static void WriteBlockTag(ByteStream& stream, int tag, uint8_t typeMarker, int flag = 0) {
        stream.WriteVInt(tag);
        stream.WriteByte(typeMarker);
        stream.WriteInt(flag);
    }
};