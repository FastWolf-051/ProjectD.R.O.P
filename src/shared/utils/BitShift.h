#pragma once

class BitShift {
public:
    BitShift() = delete;

    static inline unsigned int __ROR4__(unsigned int value, int count) {
        return (value >> count) | (value << (32 - count));
    }
};