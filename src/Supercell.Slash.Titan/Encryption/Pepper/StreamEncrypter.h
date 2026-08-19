
#pragma once

class StreamEncrypter {
public:
    virtual ~StreamEncrypter() = default;

    virtual int Encrypt(const unsigned char* input, unsigned char* output, int length) {
        return 0;
    }

    virtual int Decrypt(const unsigned char* input, unsigned char* output, int length) {
        return 0;
    }

    virtual int GetOverheadEncryption() {
        return 0;
    }

    virtual void Destruct() {}
};