#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class AvatarNameCheckRequestMessage : public PiranhaMessage {
private:
    std::string _avatarName;
public:
    void Decode() override {
        PiranhaMessage::Decode();

        _avatarName = _stream->ReadString();
    }

    int GetMessageType() override {
        return 17141;
    }

    std::string GetAvatarName() const {
        return _avatarName;
    }
};