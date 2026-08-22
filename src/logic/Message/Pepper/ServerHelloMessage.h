#pragma once

#include "../../../titan/Encryption/Library/TweetNaCl/TweetNaCl.h"
#include "../../../titan/Message/PiranhaMessage.h"

#include <array>
#include <cstdint>

class ServerHelloMessage : public PiranhaMessage {
private:
    std::array<uint8_t, 24> _serverToken{};
public:
    ServerHelloMessage() {
        TweetNaCl::RandomBytes(_serverToken.data(), 24);
    }

    void Encode() override {
        PiranhaMessage::Encode();

        _stream->WriteBytes(_serverToken);
        _stream->WriteInt24(0);
        _stream->WriteString("");
        _stream->WriteString("beta");
    }

    int GetMessageType() override {
        return 20100;
    }
};