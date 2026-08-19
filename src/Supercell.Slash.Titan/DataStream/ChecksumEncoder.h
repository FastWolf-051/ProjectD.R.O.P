#pragma once

#include <cstring>

#include "../BitShift.h"
#include "../Logic/LogicLong.h"
#include "../Debug/Debugger.h"

class ChecksumEncoder {
private:
    bool _enabled;

    unsigned int _checksum;
    unsigned int _snapshotChecksum;
public:
    ChecksumEncoder() {
        _enabled = true;

        _checksum = 0;
        _snapshotChecksum = 0;
    }

    virtual void WriteInt24(int value) {
        if (value + 0x800000 >= 16777216) {
            Debugger::Error("The argument (%d) in writeInt24() too big", value);
        }
        _checksum = (unsigned int)((value & 0xFFFFFF) + (BitShift::__ROR4__(_checksum, 0x1F) + 0x15));
    }

    virtual void WriteLong(LogicLong* value) {
        value->Encode(this);
    }

    virtual void WriteString(const char* value) {
        _checksum = (unsigned int)((value != nullptr ? strlen(value) + 28 : 27) + BitShift::__ROR4__(_checksum, 31) + 38);
    }

    virtual void WriteInt(int value) {
        _checksum = (unsigned int)(value + BitShift::__ROR4__(_checksum, 0x1F) + 9);
    }

    void EnableChecksum(bool enabled) {
        if (!_enabled || enabled) {
            if (!_enabled && enabled) {
                _checksum = _snapshotChecksum;
            }
            _enabled = enabled;
        }
        else {
            _snapshotChecksum = _checksum;
            _enabled = false;
        }
    }

    virtual bool WriteBoolean(bool value) {
        _checksum = (unsigned int)((value ? 13 : 7) + BitShift::__ROR4__(_checksum, 31));
        return value;
    }

    virtual void Destruct() {
        _checksum = 0;
        _snapshotChecksum = 0;

        _enabled = true;
    }

    virtual bool Equals(ChecksumEncoder* encoder) {
        if (encoder != nullptr) {
            if (!encoder->_enabled) {
                encoder->_checksum = encoder->_snapshotChecksum;
            }
            if (!_enabled) {
                _checksum = _snapshotChecksum;
            }
            return encoder->_checksum == _checksum;
        }
        return false;
    }

    virtual void WriteByte(unsigned char value) {
        _checksum = value + BitShift::__ROR4__(_checksum, 31) + 0xB;
    }

    void ResetChecksum() {
        _checksum = 0;
    }

    bool IsChecksumOnlyMode() {
        return true;
    }

    virtual bool IsByteStream() {
        return false;
    }

    virtual void WriteFilteredString(const char* value) {
        WriteString(value);
    }

    virtual void WriteInt8(unsigned char value) {
        if (value + 0x80 >= 256) {
            Debugger::Error("The argument (%u) in writeInt8() too big", value);
        }
        _checksum = value + BitShift::__ROR4__(_checksum, 31) + 0xB;
    }

    virtual void WriteFilteredStringReference(const char* value) {
        WriteFilteredString(value);
    }

    virtual void WriteStringReference(const char* value) {
        _checksum = (unsigned int)(strlen(value) + BitShift::__ROR4__(_checksum, 0x1F) + 0x26);
    }

    bool IsChecksumEnabled() {
        return _enabled;
    }

    unsigned int GetChecksum() {
        return _checksum;
    }

    virtual void WriteInt16(unsigned short value) {
        _checksum = (value + BitShift::__ROR4__(_checksum, 31) + 0x13);
    }

    virtual void WriteVInt(int value) {
        _checksum = (unsigned int)(value + BitShift::__ROR4__(_checksum, 0x1F) + 0x21);
    }

    virtual void WriteBytes(const unsigned char* value, int length) {
        _checksum = (unsigned int)(((value != nullptr ? length + 28 : 27) + (_checksum >> 31)) | (_checksum << 1));
    }

    virtual void WriteShort(short value) {
        _checksum = (unsigned int)(value + BitShift::__ROR4__(_checksum, 31) + 0x13);
    }

    virtual void WriteLongLong(long long value) {
        int highInt = (int)(value >> 32);
        int lowInt = (int)value;
        _checksum = (unsigned int)(lowInt + BitShift::__ROR4__((unsigned int)highInt + BitShift::__ROR4__(_checksum, 0x1F) + 0x43, 0x1f) + 0x5b);
    }

    virtual ~ChecksumEncoder() = default;
};