#pragma once

#include <cstdio>

class ByteStream;
class ChecksumEncoder;

class LogicLong {
private:
    int _highInteger;
    int _lowInteger;
public:
    LogicLong() {}

    LogicLong(int highInteger, int lowInteger) {
        _highInteger = highInteger;
        _lowInteger = lowInteger;
    }

    static long long ToLong(int highValue, int lowValue) {
        return ((long long)highValue << 32) | (unsigned int)lowValue;
    }

    LogicLong* Clone() {
        return new LogicLong(_highInteger, _lowInteger);
    }

    bool IsZero() {
        return _highInteger == 0 && _lowInteger == 0;
    }

    int GetHigherInt() const {
        return _highInteger;
    }

    int GetLowerInt() const {
        return _lowInteger;
    }

    void Decode(ByteStream* stream);

    void Encode(ChecksumEncoder* stream);

    int HashCode() {
        return _lowInteger + 31 * _highInteger;
    }

    int GetHashCode() {
        return HashCode();
    }

    bool Equals(LogicLong* logicLong) {
        if (logicLong != nullptr) {
            return logicLong->_highInteger == _highInteger && logicLong->_lowInteger == _lowInteger;
        }

        return false;
    }

    static bool Equals(LogicLong* a1, LogicLong* a2) {
        if (a1 == nullptr || a2 == nullptr) {
            return a1 == nullptr && a2 == nullptr;
        }

        return a1->_highInteger == a2->_highInteger && a1->_lowInteger == a2->_lowInteger;
    }

    const char* ToString() const {
        static char buffer[64];

        sprintf(buffer, "LogicLong(%d-%d)", _highInteger, _lowInteger);

        return buffer;
    }

    operator long long() {
        return ((long long)_highInteger << 32) | (unsigned int)_lowInteger;
    }
};