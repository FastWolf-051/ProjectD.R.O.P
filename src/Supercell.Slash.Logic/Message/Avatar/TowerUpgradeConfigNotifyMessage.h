#pragma once

#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

class TowerUpgradeConfigNotifyMessage : public PiranhaMessage {
public:
    void Encode() override {
        _stream->WriteVInt(1);
        _stream->WriteByte(192);
        _stream->WriteInt(0);

        int lengthFieldOffset = _stream->GetOffset();

        // Tower upgrades count
        _stream->WriteVInt(4);

        for (int i = 0; i < 4; ++i) {
            // Entry can't be null
            _stream->WriteBoolean(true);

            _stream->WriteTaggedVInt(i, 1);
            _stream->WriteTaggedVInt(101 * i, 2);
            _stream->WriteTaggedVInt(3 - i, 3);
            _stream->WriteTaggedVInt(0, 4);

            // Entry terminator
            _stream->WriteVInt(-1);
        }

        int endOffset = _stream->GetOffset();

        _stream->WriteIntBigEndianAt(
            endOffset - lengthFieldOffset,
            lengthFieldOffset - 4
        );

        _stream->WriteTaggedVInt(0, 2);

        // Message terminator
        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 25723;
    }
};