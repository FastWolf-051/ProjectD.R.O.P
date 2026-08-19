#pragma once

#include "../../../Supercell.Slash.Titan/Encryption/Library/TweetNaCl/TweetNaCl.h"
#include "../../../Supercell.Slash.Titan/Message/PiranhaMessage.h"

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

        _stream->WriteHexa("00-00-00-18-02-46-14-62-d3-d4-e3-61-32-db-41-ea-8a-c1-f4-08-a8-b7-f3-bc-56-db-31-3e-00-00-00-ff-ff-ff-ff-00-00-00-04-62-65-74-61");
    }

    int GetMessageType() override {
        return 20100;
    }
};
