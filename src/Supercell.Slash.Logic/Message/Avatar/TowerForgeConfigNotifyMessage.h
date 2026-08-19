#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

#include <vector>

class TowerForgeConfigNotifyMessage : public PiranhaMessage {
public:
    int EntryField0 = 0;
    int TrailingValue = 0;

    std::vector<int> EntryIntArray;

    void Encode() override {
        _stream->WriteVInt(1);
        _stream->WriteByte(192);
        _stream->WriteInt(0);

        int lengthFieldOffset = _stream->GetOffset();

        // Hardcoded count = 1
        _stream->WriteVInt(1);

        // Entry always present
        _stream->WriteBoolean(true);

        // Inlined entry encode
        _stream->WriteTaggedVInt(14, 1);

        _stream->WriteVInt(2);
        _stream->WriteByte(192);
        _stream->WriteInt(0);

        int innerOffset = _stream->GetOffset();

        _stream->WriteVInt(static_cast<int>(EntryIntArray.size()));

        for (int v : EntryIntArray) {
            _stream->WriteVInt(v);
        }

        _stream->WriteIntBigEndianAt(
            _stream->GetOffset() - innerOffset,
            innerOffset - 4
        );

        _stream->WriteVInt(-1);

        // End of entry
        int endOffset = _stream->GetOffset();

        _stream->WriteIntBigEndianAt(
            endOffset - lengthFieldOffset,
            lengthFieldOffset - 4
        );

        _stream->WriteTaggedVInt(0, 2);
        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 21473;
    }
};