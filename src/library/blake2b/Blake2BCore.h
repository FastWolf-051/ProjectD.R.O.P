#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

class Blake2BCore {
private:
    static constexpr int BlockSizeInBytes = 128;

    static constexpr uint64_t IV0 = 0x6A09E667F3BCC908ULL;
    static constexpr uint64_t IV1 = 0xBB67AE8584CAA73BULL;
    static constexpr uint64_t IV2 = 0x3C6EF372FE94F82BULL;
    static constexpr uint64_t IV3 = 0xA54FF53A5F1D36F1ULL;
    static constexpr uint64_t IV4 = 0x510E527FADE682D1ULL;
    static constexpr uint64_t IV5 = 0x9B05688C2B3E6C1FULL;
    static constexpr uint64_t IV6 = 0x1F83D9ABFB41BD6BULL;
    static constexpr uint64_t IV7 = 0x5BE0CD19137E2179ULL;

    uint8_t _buf[BlockSizeInBytes]{};
    int _bufferFilled = 0;

    uint64_t _counter0 = 0;
    uint64_t _counter1 = 0;

    uint64_t _finalizationFlag0 = 0;
    uint64_t _finalizationFlag1 = 0;

    uint64_t _h[8]{};
    uint64_t _m[16]{};

    bool _isInitialized = false;

    static constexpr uint8_t Sigma[12][16] = {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
        { 14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3 },
        { 11, 8, 12, 0, 5, 2, 15, 13, 10, 14, 3, 6, 7, 1, 9, 4 },
        { 7, 9, 3, 1, 13, 12, 11, 14, 2, 6, 5, 10, 4, 0, 15, 8 },
        { 9, 0, 5, 7, 2, 4, 10, 15, 14, 1, 11, 12, 6, 8, 3, 13 },
        { 2, 12, 6, 10, 0, 11, 8, 3, 4, 13, 7, 5, 15, 14, 1, 9 },
        { 12, 5, 1, 15, 14, 13, 4, 10, 0, 7, 6, 3, 9, 2, 8, 11 },
        { 13, 11, 7, 14, 12, 1, 3, 9, 5, 0, 15, 4, 8, 6, 2, 10 },
        { 6, 15, 14, 9, 11, 3, 0, 8, 12, 2, 13, 7, 1, 4, 10, 5 },
        { 10, 2, 8, 4, 7, 6, 1, 5, 15, 11, 9, 14, 3, 12, 13, 0 },
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
        { 14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3 }
    };

    static uint64_t BytesToUInt64(const uint8_t* data, int offset) {
        return
            ((uint64_t)data[offset + 0]) |
            ((uint64_t)data[offset + 1] << 8) |
            ((uint64_t)data[offset + 2] << 16) |
            ((uint64_t)data[offset + 3] << 24) |
            ((uint64_t)data[offset + 4] << 32) |
            ((uint64_t)data[offset + 5] << 40) |
            ((uint64_t)data[offset + 6] << 48) |
            ((uint64_t)data[offset + 7] << 56);
    }

    static void UInt64ToBytes(uint64_t value, uint8_t* data, int offset) {
        data[offset + 0] = (uint8_t)value;
        data[offset + 1] = (uint8_t)(value >> 8);
        data[offset + 2] = (uint8_t)(value >> 16);
        data[offset + 3] = (uint8_t)(value >> 24);
        data[offset + 4] = (uint8_t)(value >> 32);
        data[offset + 5] = (uint8_t)(value >> 40);
        data[offset + 6] = (uint8_t)(value >> 48);
        data[offset + 7] = (uint8_t)(value >> 56);
    }

    static void G(uint64_t& a, uint64_t& b, uint64_t& c, uint64_t& d, uint64_t x, uint64_t y) {
        a = a + b + x;
        d ^= a;
        d = (d >> 32) | (d << 32);

        c += d;
        b ^= c;
        b = (b >> 24) | (b << 40);

        a = a + b + y;
        d ^= a;
        d = (d >> 16) | (d << 48);

        c += d;
        b ^= c;
        b = (b >> 63) | (b << 1);
    }

public:
    static uint64_t BytesToUInt64Public(const uint8_t* data, int offset) {
        return BytesToUInt64(data, offset);
    }

    void Initialize(const uint64_t config[8]) {
        _isInitialized = true;

        _h[0] = IV0;
        _h[1] = IV1;
        _h[2] = IV2;
        _h[3] = IV3;
        _h[4] = IV4;
        _h[5] = IV5;
        _h[6] = IV6;
        _h[7] = IV7;

        _counter0 = 0;
        _counter1 = 0;
        _finalizationFlag0 = 0;
        _finalizationFlag1 = 0;
        _bufferFilled = 0;

        std::memset(_buf, 0, sizeof(_buf));

        for (int i = 0; i < 8; ++i) {
            _h[i] ^= config[i];
        }
    }

    void HashCore(const uint8_t* data, size_t start, size_t count) {
        if (!_isInitialized) {
            throw std::runtime_error("Blake2BCore is not initialized");
        }

        size_t offset = start;
        size_t remaining = count;

        size_t bufferRemaining =
            BlockSizeInBytes - _bufferFilled;

        if (_bufferFilled > 0 &&
            remaining > bufferRemaining) {

            std::memcpy(
                _buf + _bufferFilled,
                data + offset,
                bufferRemaining
            );

            _counter0 += BlockSizeInBytes;
            if (_counter0 == 0)
                ++_counter1;

            Compress(_buf, 0);

            offset += bufferRemaining;
            remaining -= bufferRemaining;
            _bufferFilled = 0;
        }

        while (remaining > BlockSizeInBytes) {
            _counter0 += BlockSizeInBytes;

            if (_counter0 == 0)
                ++_counter1;

            Compress(
                data,
                static_cast<int>(offset)
            );

            offset += BlockSizeInBytes;
            remaining -= BlockSizeInBytes;
        }

        if (remaining > 0) {
            std::memcpy(
                _buf + _bufferFilled,
                data + offset,
                remaining
            );

            _bufferFilled += static_cast<int>(remaining);
        }
    }

    std::vector<uint8_t> HashFinal(
        bool isEndOfLayer = false
    ) {
        if (!_isInitialized) {
            throw std::runtime_error("Blake2BCore is not initialized");
        }

        _isInitialized = false;

        _counter0 += static_cast<uint32_t>(_bufferFilled);

        _finalizationFlag0 = UINT64_MAX;

        if (isEndOfLayer)
            _finalizationFlag1 = UINT64_MAX;

        for (
            int i = _bufferFilled;
            i < BlockSizeInBytes;
            ++i
        ) {
            _buf[i] = 0;
        }

        Compress(_buf, 0);

        std::vector<uint8_t> result(64);

        for (int i = 0; i < 8; ++i) {
            UInt64ToBytes(
                _h[i],
                result.data(),
                i * 8
            );
        }

        return result;
    }

    void Compress(
        const uint8_t* block,
        int start
    ) {
        for (int i = 0; i < 16; ++i) {
            _m[i] =
                BytesToUInt64(
                    block,
                    start + (i * 8)
                );
        }

        uint64_t v[16] = {
            _h[0], _h[1], _h[2], _h[3],
            _h[4], _h[5], _h[6], _h[7],

            IV0, IV1, IV2, IV3,
            IV4 ^ _counter0,
            IV5 ^ _counter1,
            IV6 ^ _finalizationFlag0,
            IV7 ^ _finalizationFlag1
        };

        for (int round = 0; round < 12; ++round) {
            G(v[0], v[4], v[8], v[12],
              _m[Sigma[round][0]],
              _m[Sigma[round][1]]);

            G(v[1], v[5], v[9], v[13],
              _m[Sigma[round][2]],
              _m[Sigma[round][3]]);

            G(v[2], v[6], v[10], v[14],
              _m[Sigma[round][4]],
              _m[Sigma[round][5]]);

            G(v[3], v[7], v[11], v[15],
              _m[Sigma[round][6]],
              _m[Sigma[round][7]]);

            G(v[0], v[5], v[10], v[15],
              _m[Sigma[round][8]],
              _m[Sigma[round][9]]);

            G(v[1], v[6], v[11], v[12],
              _m[Sigma[round][10]],
              _m[Sigma[round][11]]);

            G(v[2], v[7], v[8], v[13],
              _m[Sigma[round][12]],
              _m[Sigma[round][13]]);

            G(v[3], v[4], v[9], v[14],
              _m[Sigma[round][14]],
              _m[Sigma[round][15]]);
        }

        for (int i = 0; i < 8; ++i) {
            _h[i] ^= v[i] ^ v[i + 8];
        }
    }
};
