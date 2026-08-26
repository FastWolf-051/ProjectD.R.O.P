#pragma once

#include <cstddef>
#include <cstdint>

class Blake2BBase {
public:
    virtual ~Blake2BBase() = default;

    virtual void Init() = 0;

    virtual void Update(const uint8_t* data, size_t start, size_t count) = 0;

    virtual uint8_t* Finish(size_t& length) = 0;

    void Update(const uint8_t* data, size_t count) {
        Update(data, 0, count);
    }
};
