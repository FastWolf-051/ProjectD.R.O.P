#pragma once

#include <cstring>
#include <array>

#include "ChecksumEncoder.h"

#include "../Logic/LogicLong.h"
#include "../Logic/LogicStringUtil.h"

class ByteStream : public ChecksumEncoder {
private:
    unsigned char* _buffer = nullptr;
    int _offset = 0;
    int _length = 0;
    int _bitOffset = 0;
    bool _ownsBuffer = true;

public:
    ByteStream() {
        _buffer = nullptr;
        _offset = 0;
        _length = 0;
        _bitOffset = 0;
        _ownsBuffer = true;
    }

    ByteStream(const unsigned char* buffer, int length) {
        _buffer = const_cast<unsigned char*>(buffer);
        _offset = 0;
        _length = length;
        _bitOffset = 0;
        _ownsBuffer = false;
    }

    ByteStream(int capacity) {
        if (capacity > 0) {
            _buffer = new unsigned char[capacity];
        }

        _offset = 0;
        _length = capacity;
        _bitOffset = 0;
        _ownsBuffer = true;
    }

    virtual ~ByteStream() {
        if (_ownsBuffer && _buffer != nullptr) {
            delete[] _buffer;
        }

        _buffer = nullptr;
    }

    virtual void WriteInt(int value) override {
        ChecksumEncoder::WriteInt(value);

        EnsureCapacity(4);
        _bitOffset = 0;

        _buffer[_offset++] = (unsigned char)(value >> 24);
        _buffer[_offset++] = (unsigned char)(value >> 16);
        _buffer[_offset++] = (unsigned char)(value >> 8);
        _buffer[_offset++] = (unsigned char)value;
    }

    virtual void WriteByte(unsigned char value) override {
        ChecksumEncoder::WriteByte(value);

        EnsureCapacity(1);
        _bitOffset = 0;

        _buffer[_offset++] = value;
    }

    virtual void WriteShort(short value) override {
        ChecksumEncoder::WriteShort(value);

        EnsureCapacity(2);
        _bitOffset = 0;

        _buffer[_offset++] = (unsigned char)(value >> 8);
        _buffer[_offset++] = (unsigned char)value;
    }

    virtual bool WriteBoolean(bool value) override {
        ChecksumEncoder::WriteBoolean(value);

        if (_bitOffset == 0) {
            EnsureCapacity(1);
            _buffer[_offset++] = 0;
        }

        if (value) {
            _buffer[_offset - 1] |= (unsigned char)(1 << _bitOffset);
        }

        _bitOffset = (_bitOffset + 1) & 7;

        return value;
    }

    virtual void WriteVInt(int value) override {
        ChecksumEncoder::WriteVInt(value);

        EnsureCapacity(5);
        _bitOffset = 0;

        unsigned char prefix = value >= 0 ? 0x80 : 0xC0;

        if (value >= -63 && value < 64) {
            _buffer[_offset++] = value < 0 ? (unsigned char)((value & 0x3F) | 0x40) : (unsigned char)(value & 0x3F);

            return;
        }

        _buffer[_offset++] = (unsigned char)((value & 0x3F) | prefix);

        value >>= 6;

        while ((value & ~0x7F) != 0) {
            _buffer[_offset++] = (unsigned char)((value & 0x7F) | 0x80);

            value >>= 7;
        }

        _buffer[_offset++] = (unsigned char)(value & 0x7F);
    }

    virtual void WriteString(const char* value) override {
        ChecksumEncoder::WriteString(value);

        if (value == nullptr) {
            WriteIntToByteArray(-1);
            return;
        }

        unsigned char* bytes = LogicStringUtil::GetBytes(value);

        if (bytes == nullptr) {
            WriteIntToByteArray(-1);
            return;
        }

        int length = LogicStringUtil::GetByteLength(bytes);

        if (length <= 900000) {
            EnsureCapacity(length + 4);

            WriteIntToByteArray(length);

            LogicStringUtil::ByteArrayCopy(bytes, 0, _buffer, _offset, length);

            _offset += length;
        }
        else {
            WriteIntToByteArray(-1);

            Debugger::Print("ByteStream::WriteString() invalid string length (%d)", length);
        }

        delete[] bytes;
    }

    void WriteStringReference(const char* value, int capacity = 900000) {
        ChecksumEncoder::WriteStringReference(value);

        if (value == nullptr) {
            WriteIntToByteArray(-1);
            return;
        }

        unsigned char* bytes = LogicStringUtil::GetBytes(value);

        if (bytes == nullptr) {
            WriteIntToByteArray(-1);
            return;
        }

        int length = LogicStringUtil::GetByteLength(bytes);

        if (length <= capacity) {
            EnsureCapacity(length + 4);

            WriteIntToByteArray(length);

            LogicStringUtil::ByteArrayCopy(bytes, 0, _buffer, _offset, length);

            _offset += length;
        }
        else {
            WriteIntToByteArray(-1);

            Debugger::Print("ByteStream::WriteStringReference() invalid string length (%d)", length);
        }

        delete[] bytes;
    }

    void WriteIntToByteArray(int value) {
        WriteInt(value);
    }

    virtual void WriteBytes(const unsigned char* value, int length) override {
        ChecksumEncoder::WriteBytes(value, length);

        if (value == nullptr) {
            WriteIntToByteArray(-1);
            return;
        }

        if (length < 0) {
            WriteIntToByteArray(-1);
            return;
        }

        EnsureCapacity(length + 4);

        WriteIntToByteArray(length);

        if (length > 0) {
            LogicStringUtil::ByteArrayCopy(const_cast<unsigned char*>(value), 0, _buffer, _offset, length);

            _offset += length;
        }
    }

    template <std::size_t N>
    void WriteBytes(const std::array<unsigned char, N>& data) {
        WriteBytes(data.data(), static_cast<int>(data.size()));
    }

    virtual void WriteFilteredString(const char* value) override {
        ChecksumEncoder::WriteFilteredString(value);
        WriteString(value);
    }

    virtual void WriteFilteredStringReference(const char* value) override {
        ChecksumEncoder::WriteFilteredStringReference(value);
        WriteFilteredString(value);
    }

    virtual void WriteLongLong(long long value) override {
        ChecksumEncoder::WriteLongLong(value);

        int highInt = (int)(value >> 32);
        int lowInt = (int)value;

        WriteIntToByteArray(highInt);
        WriteIntToByteArray(lowInt);
    }

    virtual void WriteInt24(int value) override {
        ChecksumEncoder::WriteInt24(value);

        EnsureCapacity(3);
        _bitOffset = 0;

        _buffer[_offset++] = (unsigned char)(value >> 16);
        _buffer[_offset++] = (unsigned char)(value >> 8);
        _buffer[_offset++] = (unsigned char)value;
    }

    virtual void WriteInt16(unsigned short value) override {
        ChecksumEncoder::WriteInt16(value);

        EnsureCapacity(2);
        _bitOffset = 0;

        _buffer[_offset++] = (unsigned char)(value >> 8);
        _buffer[_offset++] = (unsigned char)value;
    }

    virtual void WriteInt8(unsigned char value) override {
        ChecksumEncoder::WriteInt8(value);

        EnsureCapacity(1);
        _bitOffset = 0;

        _buffer[_offset++] = value;
    }

    LogicLong* ReadLong() {
        LogicLong* value = new LogicLong();

        value->Decode(this);

        return value;
    }

    void WriteLong(LogicLong* value) {
        if (value == nullptr) {
            WriteInt(0);
            WriteInt(0);
            return;
        }

        value->Encode(this);
    }

    void WriteVLong(LogicLong* value) {
        if (value == nullptr) {
            WriteVInt(0);
            WriteVInt(0);
            return;
        }

        WriteVInt(value->GetHigherInt());
        WriteVInt(value->GetLowerInt());
    }

    LogicLong* ReadVLong() {
        return new LogicLong(ReadVInt(), ReadVInt());
    }

    long long ReadLongLong() {
        int highInt = ReadInt();
        int lowInt = ReadInt();

        return ((long long)highInt << 32) | (unsigned int)lowInt;
    }

    bool ReadBoolean() {
        if (_bitOffset == 0) {
            ++_offset;
        }

        bool value =
            (_buffer[_offset - 1] & (1 << _bitOffset)) != 0;

        _bitOffset = (_bitOffset + 1) & 7;

        return value;
    }

    int ReadInt() {
        _bitOffset = 0;

        return ((int)_buffer[_offset++] << 24) |
               ((int)_buffer[_offset++] << 16) |
               ((int)_buffer[_offset++] << 8) |
                (int)_buffer[_offset++];
    }

    unsigned char ReadByte() {
        _bitOffset = 0;

        return _buffer[_offset++];
    }

    short ReadShort() {
        _bitOffset = 0;

        return (short)(
            ((int)_buffer[_offset++] << 8) |
             (int)_buffer[_offset++]
        );
    }

    int ReadVInt() {
        _bitOffset = 0;

        unsigned char first = _buffer[_offset++];

        int value = first & 0x3F;

        if ((first & 0x80) == 0) {
            return (first & 0x40) != 0 ? value | (int)0xFFFFFFC0 : value;
        }

        int shift = 6;

        while (shift < 32) {
            unsigned char b = ReadByte();

            value |= (b & 0x7F) << shift;

            if ((b & 0x80) == 0) {
                break;
            }

            shift += 7;
        }

        if ((first & 0x40) != 0) {
            value |= -1 << shift;
        }

        return value;
    }

    char* ReadString(int maxCapacity = 9000000) {
        int length = ReadBytesLength();

        if (length <= -1) {
            return nullptr;
        }

        if (length <= maxCapacity) {
            char* value = new char[length + 1];

            if (length > 0) {
                std::memcpy(value, _buffer + _offset, length);
            }

            value[length] = '\0';

            _offset += length;

            return value;
        }

        return nullptr;
    }

    int ReadBytesLength() {
        _bitOffset = 0;

        return ((int)_buffer[_offset++] << 24) |
               ((int)_buffer[_offset++] << 16) |
               ((int)_buffer[_offset++] << 8) |
                (int)_buffer[_offset++];
    }

    unsigned char* ReadBytes(int length, int maxCapacity) {
        _bitOffset = 0;

        if (length < 0) {
            return nullptr;
        }

        if (length <= maxCapacity) {
            unsigned char* array = new unsigned char[length];

            if (length > 0) {
                LogicStringUtil::ByteArrayCopy(_buffer, _offset, array, 0, length);
            }

            _offset += length;

            return array;
        }

        return nullptr;
    }

    char* ReadStringReference(int maxCapacity = 900000) {
        int length = ReadBytesLength();

        if (length <= -1) {
            char* value = new char[1];
            value[0] = '\0';

            return value;
        }

        if (length <= maxCapacity) {
            char* value = new char[length + 1];

            if (length > 0) {
                std::memcpy(value, _buffer + _offset, length);
            }

            value[length] = '\0';

            _offset += length;

            return value;
        }

        char* value = new char[1];
        value[0] = '\0';

        return value;
    }

    char* ReadFilteredString() {
        return ReadString();
    }

    char* ReadFilteredStringReference(int maxCapacity) {
        return ReadStringReference(maxCapacity);
    }

    unsigned char ReadInt8() {
        return ReadByte();
    }

    unsigned short ReadInt16() {
        _bitOffset = 0;

        return (unsigned short)(
            ((unsigned int)_buffer[_offset++] << 8) |
             (unsigned int)_buffer[_offset++]
        );
    }

    int ReadInt24() {
        _bitOffset = 0;

        return((int)_buffer[_offset++] << 16) |
              ((int)_buffer[_offset++] << 8) |
               (int)_buffer[_offset++];
    }

    void SetByteArray(const unsigned char* buffer, int length) {
        if (_ownsBuffer && _buffer != nullptr) {
            delete[] _buffer;
        }

        _buffer = nullptr;
        _offset = 0;
        _length = 0;
        _bitOffset = 0;
        _ownsBuffer = true;

        if (buffer == nullptr || length <= 0) {
            return;
        }

        _buffer = new unsigned char[length];

        std::memcpy(_buffer, buffer, length);

        _length = length;
    }

    void SetOffset(int offset) {
        if (offset < 0) {
            offset = 0;
        }

        _offset = offset;
        _bitOffset = 0;
    }

    int GetLength() {
        return _offset;
    }

    int GetOffset() {
        return _offset;
    }

    int GetWrittenLength() {
        return _offset;
    }

    int GetCapacity() {
        return _length;
    }

    int GetVIntSizeInBytes(int value) {
        if (value >= 0) {
            if (value < 0x40) return 1;
            if (value < 0x2000) return 2;
            if (value < 0x100000) return 3;
            if (value < 0x8000000) return 4;
            return 5;
        }
        if (value > -64) return 1;
        if (value > -8192) return 2;
        if (value > -1048576) return 3;
        if (value > -134217728) return 4;
        return 5;
    }

    unsigned char* GetByteArray() {
        return _buffer;
    }

    void ResetOffset() {
        _offset = 0;
        _bitOffset = 0;
    }

    void Clear(int capacity) {
        if (_ownsBuffer && _buffer != nullptr) {
            delete[] _buffer;
        }

        _buffer = nullptr;

        if (capacity > 0) {
            _buffer = new unsigned char[capacity];
        }

        _offset = 0;
        _length = capacity;
        _bitOffset = 0;
        _ownsBuffer = true;
    }

    void EnsureCapacity(int capacity) {
        if (capacity <= 0) return;
        if (_offset + capacity <= _length) return;

        int required = _offset + capacity;
        int newLength = _length > 0 ? _length : 100;

        while (newLength < required) {
            newLength += capacity + 100;
        }

        unsigned char* temporaryBuffer =
            new unsigned char[newLength];

        if (_buffer != nullptr && _offset > 0) {
            std::memcpy(temporaryBuffer, _buffer, _offset);
        }

        if (_ownsBuffer && _buffer != nullptr) {
            delete[] _buffer;
        }

        _buffer = temporaryBuffer;
        _length = newLength;
        _ownsBuffer = true;
    }

    bool IsAtEnd() {
        return _offset >= _length;
    }

    void WriteHexa(const char* hex) {
        if (hex == nullptr) return;

        int rawLength = (int)std::strlen(hex);

        // Filter out any non-hex-digit characters (e.g. '-', ' ')
        char* clean = new char[rawLength + 1];
        int cleanLength = 0;

        for (int i = 0; i < rawLength; ++i) {
            char c = hex[i];
            if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
                clean[cleanLength++] = c;
            }
        }
        clean[cleanLength] = '\0';

        if (cleanLength % 2 != 0) {
            Debugger::Error("hexa string must have even length");
            delete[] clean;
            return;
        }

        int byteCount = cleanLength / 2;

        EnsureCapacity(byteCount);

        for (int i = 0; i < cleanLength; i += 2) {
            unsigned char value = 0;

            for (int j = 0; j < 2; ++j) {
                char c = clean[i + j];

                value = (unsigned char)(value << 4);

                if (c >= '0' && c <= '9') {
                    value = (unsigned char)(value + (c - '0'));
                }
                else if (c >= 'A' && c <= 'F') {
                    value = (unsigned char)(value + (c - 'A' + 10));
                }
                else if (c >= 'a' && c <= 'f') {
                    value = (unsigned char)(value + (c - 'a' + 10));
                }
            }
            WriteByte(value);
        }

        delete[] clean;
    }

    void WriteVInt64(long long value) {
        EnsureCapacity(10);
        _bitOffset = 0;

        unsigned long long v = static_cast<unsigned long long>(value);

        unsigned char prefix = value < 0 ? 0xC0 : 0x80;

        if (value >= -63 && value < 64) {
            if (value < 0) {
                _buffer[_offset++] =
                    static_cast<unsigned char>((v & 0x3FULL) | 0x40);
            }
            else {
                _buffer[_offset++] =
                    static_cast<unsigned char>(v & 0x3FULL);
            }

            return;
        }

        _buffer[_offset++] =
            static_cast<unsigned char>((v & 0x3FULL) | prefix);

        v >>= 6;

        while (true) {
            unsigned char byte =
                static_cast<unsigned char>(v & 0x7FULL);

            v >>= 7;

            if (v == 0) {
                _buffer[_offset++] = byte;
                break;
            }

            _buffer[_offset++] =
                static_cast<unsigned char>(byte | 0x80);
        }
    }

    long long ReadVInt64() {
        _bitOffset = 0;

        unsigned char first = _buffer[_offset++];

        unsigned long long value =
            static_cast<unsigned long long>(first & 0x3F);

        if ((first & 0x80) == 0) {
            if ((first & 0x40) != 0) {
                value |= 0xFFFFFFFFFFFFFFC0ULL;
            }

            return static_cast<long long>(value);
        }

        int shift = 6;

        while (shift < 64) {
            unsigned char b = _buffer[_offset++];

            value |=
                static_cast<unsigned long long>(b & 0x7F)
                << shift;

            if ((b & 0x80) == 0) {
                break;
            }

            shift += 7;
        }

        if ((first & 0x40) != 0 && shift < 64) {
            value |= (~0ULL) << shift;
        }

        return static_cast<long long>(value);
    }

    // Project R.I.S.E specific
    void WriteTaggedVInt(int value, int tag) {
        WriteVInt(tag);

        int byteCount = GetVIntSizeInBytes(value);

        WriteByte((unsigned char)(byteCount | 0x80));
        WriteVInt(value);
    }

    int ReadTaggedVInt() {
        ReadVInt(); // tag

        unsigned char byteCount = ReadByte(); // wire type

        return ReadVInt(); // value
    }

    void WriteIntBigEndianAt(int position, int value) {
        _buffer[position++] = (unsigned char)(value >> 24);
        _buffer[position++] = (unsigned char)(value >> 16);
        _buffer[position++] = (unsigned char)(value >> 8);
        _buffer[position++] = (unsigned char)value;
    }
};