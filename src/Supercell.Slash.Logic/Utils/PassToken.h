#pragma once

#include <string>
#include <random>

class PassToken {
public:
    static const char* Generate() {
        static std::string token;

        static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

        std::random_device rd;

        token.clear();
        token.reserve(57);

        for (int i = 0; i < 24; ++i) {
            token += alphabet[rd() % 64];
        }

        token += '.';

        for (int i = 0; i < 32; ++i) {
            token += alphabet[rd() % 64];
        }

        return token.c_str();
    }
};
