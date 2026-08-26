#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>

#include "../../protocol/pepper/keys/PepperKeys.h"

class ServerConfig {
private:
    static void LoadKeys() {
        PepperKey::SERVER_SK = FromHex(ServerConfig::GetString("SERVER_SK"));
        PepperKey::SERVER_PK = FromHex(ServerConfig::GetString("SERVER_PK"));
    }
public:
    static void LoadFile(const std::string& path = "config/.config.env") {
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cout << "config file not found (.config.env)" << std::endl;
            return;
        }

        std::string line;

        while (std::getline(file, line)) {
            std::string trimmed = Trim(line);

            if (trimmed.empty() || trimmed[0] == '#') continue;

            std::size_t separator = trimmed.find('=');

            if (separator == std::string::npos || separator == 0) continue;

            std::string key = Trim(trimmed.substr(0, separator));
            std::string value = Trim(trimmed.substr(separator + 1));

            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            }

        #ifdef _WIN32
            _putenv_s(key.c_str(), value.c_str());
        #else
            setenv(key.c_str(), value.c_str(), 1);
        #endif
        }
    }

    static std::string Trim(const std::string& str) {
        const char* whitespace = " \t\n\r\f\v";

        std::size_t start = str.find_first_not_of(whitespace);

        if (start == std::string::npos) return "";

        std::size_t end = str.find_last_not_of(whitespace);

        return str.substr(start, end - start + 1);
    }

    static void Load() {
        LoadFile();
        LoadKeys();
    }

    static const char* GetString(const std::string& key) {
        return std::getenv(key.c_str());
    }

    static int GetInt(const std::string& key) {
        const char* value = GetString(key);

        if (value == nullptr) return 0;

        return std::stoi(value);
    }

private:
    // helper methods
    static unsigned char Hex(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;

        return c - 'A' + 10;
    }

    static std::vector<unsigned char> FromHex(const char* hex) {
        if (hex == nullptr) return {};

        std::size_t length = std::strlen(hex);

        if (length % 2 != 0) {
            throw std::invalid_argument("hex length isn't even");
        }

        std::vector<unsigned char> result(length / 2);

        for (std::size_t i = 0; i < length; i += 2) {
            result[i / 2] = static_cast<unsigned char>((Hex(hex[i]) << 4) | Hex(hex[i + 1]));
        }

        return result;
    }
};