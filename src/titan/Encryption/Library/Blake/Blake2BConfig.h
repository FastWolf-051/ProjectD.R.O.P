#pragma once

#include <cstdint>
#include <vector>

class Blake2BConfig {
public:
    Blake2BConfig()
        : OutputSize(24) {
    }

    std::vector<uint8_t> Key;
    int OutputSize;
    std::vector<uint8_t> Personalization;
    std::vector<uint8_t> Salt;

    int GetOutputSizeInBits() const {
        return OutputSize * 8;
    }

    void SetOutputSizeInBits(int value) {
        OutputSize = value / 8;
    }
};
