#pragma once

#include <vector>
#include <cstdint>

class PepperKey {
public:
    inline static std::vector<unsigned char> CLIENT_SK;
    inline static std::vector<unsigned char> SERVER_PK;
};