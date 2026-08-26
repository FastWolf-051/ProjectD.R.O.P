#pragma once

#include <vector>
#include "../../library/tweetnacl/TweetNaCl.h"

using bytearray = std::vector<unsigned char>;

class PepperCrypto {
public:
    static bytearray Secretbox(const bytearray& input, const bytearray& nonce, const bytearray& key){
        return TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet(input, nonce, key);
    }

    static bytearray SecretboxOpen(const bytearray& input, const bytearray& nonce, const bytearray& key) {
        return TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet_open(input, nonce, key);
    }

    static void GenerateRandom(bytearray& output) {
        TweetNaCl::RandomBytes(output);
    }

    static void GenerateKeyPair(bytearray& publicKey, bytearray& secretKey) {
        publicKey = TweetNaCl::CryptoBoxKeypair(secretKey);
    }
};