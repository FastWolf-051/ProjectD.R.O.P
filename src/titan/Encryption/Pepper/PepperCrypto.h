#pragma once

#include <vector>
#include <stdexcept>

#include "../Library/TweetNaCl/TweetNaCl.h"

typedef std::vector<unsigned char>& char_array;

class PepperCrypto {
public:
    static std::vector<unsigned char> Secretbox(const char_array input, const char_array nonce, const char_array secretKey) {
        return TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet(input, nonce, secretKey);
    }

    static std::vector<unsigned char> SecretboxOpen(const char_array input, const char_array nonce, const char_array secretKey) {
        return TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet_open(input, nonce, secretKey);
    }

    static void GenerateRandom(char_array output) {
        TweetNaCl::RandomBytes(output);
    }

    static void GenerateKeyPair(char_array publicKey, char_array secretKey) {
        publicKey = TweetNaCl::CryptoBoxKeypair(secretKey);
    }
};