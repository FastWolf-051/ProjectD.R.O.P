#pragma once

#include <cstdarg>
#include <stdio.h>

class Debugger {
public:
    Debugger() = delete;

    static inline void Error(const char* error, ...) {
        printf("%s[Error]: ", "\x1b[31m");

        va_list args;
        va_start(args, error);
        vprintf(error, args);
        va_end(args);

        printf("%s\n", "\x1b[0m");
    }

    static inline void Warning(const char* warning, ...) {
        printf("%s[Warning]: ", "\x1b[33m");

        va_list args;
        va_start(args, warning);
        vprintf(warning, args);
        va_end(args);

        printf("%s\n", "\x1b[0m");
    }

    static inline void Print(const char* log, ...) {
        printf("%s[Log]: ", "\x1b[36m");

        va_list args;
        va_start(args, log);
        vprintf(log, args);
        va_end(args);

        printf("%s\n", "\x1b[0m");
    }
};