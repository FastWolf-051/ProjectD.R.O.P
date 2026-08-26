
#pragma once

#include <vector>
#include <cstring>
#include <algorithm>

#include "StreamEncrypter.h"
#include "PepperCrypto.h"

class PepperEncrypter : public StreamEncrypter {
private:
    unsigned char* _key;
    unsigned char* _nonce;

public:
    PepperEncrypter(unsigned char* key, unsigned char* nonce) {
        _key = key;
        _nonce = nonce;
    }

    int Encrypt(const unsigned char* input, unsigned char* output, int length) override {
        if (input == nullptr || output == nullptr || length < 0) {
            return -1;
        }

        NextNonce();

        std::vector<unsigned char> inputVector(input, input + length);
        std::vector<unsigned char> nonceVector(_nonce, _nonce + 24);
        std::vector<unsigned char> keyVector(_key, _key + 32);

        std::vector<unsigned char> result;

        try {
            result = PepperCrypto::Secretbox(inputVector, nonceVector, keyVector);
        }
        catch (...) {
            return -1;
        }

        const int expectedLength = length + 16;

        if (static_cast<int>(result.size()) != expectedLength) {
            return -1;
        }

        std::memcpy(output, result.data(), result.size());

        return 0;
    }

    int Decrypt(const unsigned char* input, unsigned char* output, int length) override {
        if (input == nullptr || output == nullptr || length < 16) {
            return -1;
        }

        NextNonce();

        std::vector<unsigned char> inputVector(input, input + length);
        std::vector<unsigned char> nonceVector(_nonce, _nonce + 24);
        std::vector<unsigned char> keyVector(_key, _key + 32);

        try {
            std::vector<unsigned char> result = PepperCrypto::SecretboxOpen(inputVector, nonceVector, keyVector);

            if (result.empty() && length > 16) {
                return -1;
            }

            if (!result.empty()) {
                std::memcpy(output, result.data(), result.size());
            }

            return 0;
        }
        catch (...) {
            return -1;
        }
    }

    int GetOverheadEncryption() override {
        return 16;
    }

    virtual ~PepperEncrypter() = default;
private:
    void NextNonce() {
        int carry = 2;

        for (int i = 0; i < 24 && carry != 0; ++i) {

            int sum = static_cast<int>(_nonce[i]) + carry;

            _nonce[i] = static_cast<unsigned char>(sum & 0xFF);

            carry = sum >> 8;
        }
    }
};