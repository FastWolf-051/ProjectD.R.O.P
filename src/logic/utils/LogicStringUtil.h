#pragma once

#include <cstring>
#include <cstdio>

class LogicStringUtil {
public:
    static void ByteArrayCopy(unsigned char* source, int sourceOffset, unsigned char* destination, int destinationOffset, int count) {
        memcpy(destination + destinationOffset, source + sourceOffset,count);
    }

    static unsigned char* GetBytes(const char* value) {
        if (value == nullptr) return nullptr;

        int length = strlen(value);

        unsigned char* bytes = new unsigned char[length + 1];

        memcpy(bytes, value, length);

        bytes[length] = '\0';

        return bytes;
    }

    static int GetByteLength(unsigned char* bytes) {
        if (bytes == nullptr) return 0;

        return strlen((const char*)bytes);
    }

    static const char* ToString(int value) {
        thread_local char buffer[32];

        std::snprintf(buffer, sizeof(buffer), "%d", value);
        return buffer;
    }
};