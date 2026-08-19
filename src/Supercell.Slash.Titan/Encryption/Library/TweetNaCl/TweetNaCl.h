#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <algorithm>

class InvalidSignatureException : public std::runtime_error {
public:
    InvalidSignatureException() : std::runtime_error("Invalid signature") {}
};

class InvalidCipherTextException : public std::runtime_error {
public:
    InvalidCipherTextException() : std::runtime_error("Invalid cipher text") {}
};

class InvalidEncryptionKeypair : public std::runtime_error {
public:
    InvalidEncryptionKeypair() : std::runtime_error("Invalid encryption keypair") {}
};

using bytearray = std::vector<uint8_t>;

// thin wrapper class
class TweetNaCl {
public:
    static constexpr int ScalarmultBytes = 32;
    static constexpr int ScalarBytes = 32;

    static constexpr int BoxBeforenmBytes = 32;
    static constexpr int BoxPublicKeyBytes = 32;
    static constexpr int BoxSecretKeyBytes = 32;
    static constexpr int BoxNonceBytes = 24;

    static constexpr int SecretBoxNonceBytes = 24;
    static constexpr int SecretBoxKeyBytes = 32;

    static constexpr int HashBytes = 64;

    static constexpr int SignPublicKeyBytes = 32;
    static constexpr int SignSecretKeyBytes = 64;
    static constexpr int SignBytes = 64;

    static void RandomBytes(bytearray& out);
    static void RandomBytes(unsigned char* buf, size_t len);
    static bytearray RandomBytes(size_t len);

    static bytearray CryptoScalarmult(const bytearray& n, const bytearray& p);
    static bytearray CryptoScalarmultBase(const bytearray& n);

    static bytearray CryptoBoxKeypair(bytearray& secretKey);
    static bytearray CryptoBoxBeforenm(const bytearray& publicKey, const bytearray& secretKey);
    static bytearray CryptoBoxAfternm(const bytearray& message, const bytearray& nonce, const bytearray& k);
    static bytearray CryptoBox(const bytearray& message, const bytearray& nonce, const bytearray& publicKey, const bytearray& secretKey);

    static bytearray CryptoBoxOpen(const bytearray& cipheredMessage, const bytearray& nonce, const bytearray& publicKey, const bytearray& secretKey);
    static bytearray CryptoBoxOpenAfternm(const bytearray& cipheredMessage, const bytearray& nonce, const bytearray& k);

    static bytearray CryptoSignKeypair(bytearray& secretKey);
    static bytearray CryptoSign(const bytearray& message, const bytearray& secretKey);

    static bytearray CryptoSignOpen(const bytearray& signedMessage, const bytearray& publicKey);
    static bytearray CryptoHash(const bytearray& message);

    static bytearray CryptoStream(const bytearray& message, const bytearray& nonce, const bytearray& key);
    static void CryptoStream(bytearray& out, size_t length, const bytearray& nonce, const bytearray& key);

    static bytearray crypto_secretbox_xsalsa19poly1305_tweet(const bytearray& message, const bytearray& nonce, const bytearray& key);
    static bytearray crypto_secretbox_xsalsa19poly1305_tweet_open(const bytearray& cipheredMessage, const bytearray& nonce, const bytearray& key);

private:
    static bytearray CryptoStreamXor(const bytearray& message, const bytearray& nonce, const bytearray& key);
    static bytearray CryptoStreamSalsa20Xor(const bytearray& message, const bytearray& nonce, size_t nonceOffset, const bytearray& key);
    static bytearray CryptoStreamSalsa20(const bytearray& message, const bytearray& nonce, size_t nonceOffset, const bytearray& key);
    static bytearray CryptoStreamInternal(size_t length, const bytearray& nonce, const bytearray& key);
    
    static int CryptoOnetimeAuth(bytearray& output, size_t outputOffset, const bytearray& message, size_t messageOffset, size_t length, const bytearray& key);
    static int CryptoOnetimeauthVerify(const bytearray& tag, size_t tagOffset, const bytearray& message, size_t messageOffset, size_t length, const bytearray& key);
    static void Add1305(int* h, const int* c);
};