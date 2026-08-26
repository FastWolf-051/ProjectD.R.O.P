#include "TweetNaCl.h"

#include <random>
#include <cstring>
#include <limits>

extern "C" void randombytes(unsigned char* buf, unsigned long long len) {
    static thread_local std::random_device rd;
    static thread_local std::mt19937_64 gen(rd());
    static thread_local std::uniform_int_distribution<int> dist(0, 255);

    for (unsigned long long i = 0; i < len; ++i) {
        buf[i] = static_cast<unsigned char>(dist(gen));
    }
}

extern "C" {
    #include "tweetnacl_impl.c"
}

void TweetNaCl::RandomBytes(bytearray& out) {
    if (out.empty()) return;

    randombytes(out.data(), static_cast<unsigned long long>(out.size()));
}

void TweetNaCl::RandomBytes(unsigned char* buf, size_t len) {
    randombytes(buf, static_cast<unsigned long long>(len));
}

bytearray TweetNaCl::RandomBytes(size_t len) {
    bytearray out(len);

    RandomBytes(out);

    return out;
}

bytearray TweetNaCl::CryptoScalarmult(const bytearray& n, const bytearray& p) {
    bytearray q(32);

    if (crypto_scalarmult(q.data(), n.data(), p.data()) != 0) {
        throw InvalidEncryptionKeypair();
    }

    return q;
}

bytearray TweetNaCl::CryptoScalarmultBase(const bytearray& n) {
    bytearray q(32);

    if (crypto_scalarmult_base(q.data(), n.data()) != 0) {
        throw InvalidEncryptionKeypair();
    }

    return q;
}

bytearray TweetNaCl::CryptoBoxKeypair(bytearray& secretKey) {
    secretKey.resize(32);

    bytearray publicKey(32);

    if (crypto_box_keypair(publicKey.data(), secretKey.data()) != 0) {
        throw InvalidEncryptionKeypair();
    }

    return publicKey;
}

bytearray TweetNaCl::CryptoBoxBeforenm(const bytearray& publicKey, const bytearray& secretKey) {
    bytearray k(32);

    if (crypto_box_beforenm(k.data(), publicKey.data(), secretKey.data()) != 0) {
        throw InvalidEncryptionKeypair();
    }

    return k;
}

bytearray TweetNaCl::CryptoBoxAfternm(const bytearray& message, const bytearray& nonce, const bytearray& k) {
    bytearray m(32 + message.size(), 0);

    std::copy(message.begin(), message.end(), m.begin() + 32);

    bytearray c(m.size(), 0);

    if (crypto_box_afternm(c.data(), m.data(), static_cast<unsigned long long>(m.size()), nonce.data(), k.data()) != 0) {
        throw InvalidCipherTextException();
    }

    return bytearray(c.begin() + 16, c.end());
}

bytearray TweetNaCl::CryptoBoxOpenAfternm(const bytearray& cipheredMessage, const bytearray& nonce, const bytearray& k) {
    bytearray c(16 + cipheredMessage.size(), 0);

    std::copy(cipheredMessage.begin(), cipheredMessage.end(), c.begin() + 16);

    bytearray m(c.size(), 0);

    if (crypto_box_open_afternm(m.data(), c.data(), static_cast<unsigned long long>(c.size()), nonce.data(), k.data()) != 0) {
        throw InvalidCipherTextException();
    }

    return bytearray(m.begin() + 32, m.end());
}

bytearray TweetNaCl::CryptoBox(const bytearray& message, const bytearray& nonce, const bytearray& publicKey, const bytearray& secretKey) {
    bytearray m(32 + message.size(), 0);

    std::copy(message.begin(), message.end(), m.begin() + 32);

    bytearray c(m.size(), 0);

    if (crypto_box(c.data(), m.data(), static_cast<unsigned long long>(m.size()), nonce.data(), publicKey.data(), secretKey.data()) != 0) {
        throw InvalidCipherTextException();
    }

    return bytearray(c.begin() + 16, c.end());
}

bytearray TweetNaCl::CryptoBoxOpen(const bytearray& cipheredMessage, const bytearray& nonce, const bytearray& publicKey, const bytearray& secretKey) {
    bytearray c(16 + cipheredMessage.size(), 0);

    std::copy(cipheredMessage.begin(), cipheredMessage.end(), c.begin() + 16);

    bytearray m(c.size(), 0);

    if (crypto_box_open(m.data(), c.data(), static_cast<unsigned long long>(c.size()), nonce.data(), publicKey.data(), secretKey.data()) != 0) {
        throw InvalidCipherTextException();
    }

    return bytearray(m.begin() + 32, m.end());
}

bytearray TweetNaCl::CryptoSignKeypair(bytearray& secretKey) {
    bytearray publicKey(32);

    secretKey.resize(64);

    if (crypto_sign_keypair(publicKey.data(), secretKey.data()) != 0) {
        throw InvalidSignatureException();
    }

    return publicKey;
}

bytearray TweetNaCl::CryptoSign(const bytearray& message, const bytearray& secretKey) {
    bytearray sm(64 + message.size());

    unsigned long long smlen = 0;

    if (crypto_sign(sm.data(), &smlen, message.data(), static_cast<unsigned long long>(message.size()), secretKey.data()) != 0) {
        throw InvalidSignatureException();
    }

    sm.resize(static_cast<size_t>(smlen));

    return sm;
}

bytearray TweetNaCl::CryptoSignOpen(const bytearray& signedMessage, const bytearray& publicKey) {
    bytearray message(signedMessage.size());

    unsigned long long messageLength = 0;

    if (crypto_sign_open(message.data(), &messageLength, signedMessage.data(), static_cast<unsigned long long>(signedMessage.size()), publicKey.data()) != 0) {
        throw InvalidSignatureException();
    }

    message.resize(static_cast<size_t>(messageLength));

    return message;
}

bytearray TweetNaCl::CryptoHash(const bytearray& message) {
    bytearray hash(64);

    const unsigned char* data = message.empty() ? nullptr : message.data();

    if (crypto_hash(hash.data(), data, static_cast<unsigned long long>(message.size())) != 0) {
        throw std::runtime_error("crypto_hash failed");
    }

    return hash;
}

bytearray TweetNaCl::CryptoStream(const bytearray& message, const bytearray& nonce, const bytearray& key) {
    bytearray out(message.size());

    const unsigned char* input = message.empty() ? nullptr : message.data();
    unsigned char* output = out.empty() ? nullptr : out.data();

    if (crypto_stream_xor(output, input, static_cast<unsigned long long>(message.size()), nonce.data(), key.data()) != 0) {
        throw InvalidCipherTextException();
    }

    return out;
}

void TweetNaCl::CryptoStream(bytearray& out, size_t length, const bytearray& nonce, const bytearray& key) {
    out.resize(length);

    if (length == 0) return;

    if (crypto_stream(out.data(), static_cast<unsigned long long>(length), nonce.data(), key.data()) != 0) {
        throw InvalidCipherTextException();
    }
}

bytearray TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet(const bytearray& message, const bytearray& nonce, const bytearray& key) {
    bytearray m(message.size() + 32, 0);

    std::copy(message.begin(), message.end(), m.begin() + 32);

    bytearray c(m.size(), 0);

    int rc = crypto_secretbox(c.data(), m.data(), static_cast<unsigned long long>(m.size()), nonce.data(), key.data());

    if (rc != 0) {
        throw InvalidCipherTextException();
    }

    return bytearray(c.begin() + 16, c.end());
}

bytearray TweetNaCl::crypto_secretbox_xsalsa19poly1305_tweet_open(const bytearray& cipheredMessage, const bytearray& nonce, const bytearray& key) {
    const size_t wireLen = cipheredMessage.size();

    bytearray c(wireLen + 16);

    std::memset(c.data(), 0, 16);

    std::memcpy(c.data() + 16, cipheredMessage.data(), wireLen);

    bytearray m(c.size());

    int rc = crypto_secretbox_open(m.data(), c.data(), static_cast<unsigned long long>(c.size()), nonce.data(), key.data());

    if (rc != 0) {
        throw InvalidCipherTextException();
    }

    return bytearray(m.begin() + 32, m.end());
}

bytearray TweetNaCl::CryptoStreamXor(const bytearray& message, const bytearray& nonce, const bytearray& key) {
    bytearray output(message.size());

    crypto_stream_xor(output.data(), message.data(), static_cast<unsigned long long>(message.size()), nonce.data(), key.data());

    return output;
}

bytearray TweetNaCl::CryptoStreamSalsa20Xor(const bytearray& message, const bytearray& nonce, size_t nonceOffset, const bytearray& key) {
    bytearray output(message.size());

    crypto_stream_salsa20_xor(output.data(), message.data(), static_cast<unsigned long long>(message.size()), nonce.data() + nonceOffset, key.data());

    return output;
}

bytearray TweetNaCl::CryptoStreamSalsa20(const bytearray& message, const bytearray& nonce, size_t nonceOffset, const bytearray& key) {
    bytearray output(message.size());

    crypto_stream_salsa20(output.data(), static_cast<unsigned long long>(message.size()), nonce.data() + nonceOffset, key.data());

    return output;
}

bytearray TweetNaCl::CryptoStreamInternal(size_t length, const bytearray& nonce, const bytearray& key) {
    bytearray output(length);

    crypto_stream_salsa20(output.data(), static_cast<unsigned long long>(length), nonce.data(), key.data());

    return output;
}

int TweetNaCl::CryptoOnetimeAuth(bytearray& output, size_t outputOffset, const bytearray& message, size_t messageOffset, size_t length, const bytearray& key) {
    return crypto_onetimeauth(output.data() + outputOffset, message.data() + messageOffset, static_cast<unsigned long long>(length), key.data());
}

int TweetNaCl::CryptoOnetimeauthVerify(const bytearray& tag, size_t tagOffset, const bytearray& message, size_t messageOffset, size_t length, const bytearray& key) {
    return crypto_onetimeauth_verify(tag.data() + tagOffset, message.data() + messageOffset, static_cast<unsigned long long>(length), key.data());
}

void TweetNaCl::Add1305(int* h, const int* c) {
    int u = 0;

    for (int j = 0; j < 17; ++j) {
        u += h[j] + c[j];
        h[j] = u & 255;
        u >>= 8;
    }
}