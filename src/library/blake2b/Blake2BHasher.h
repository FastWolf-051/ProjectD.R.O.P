#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

#include "Blake2BBase.h"
#include "Blake2BConfig.h"
#include "Blake2BCore.h"
#include "Blake2Builder.h"

class Blake2BHasher : public Blake2BBase {
private:
    Blake2BConfig _config;
    Blake2BCore _core;

    std::vector<uint8_t> _key;
    int _outputSize = 0;

    uint64_t* _rawConfig = nullptr;

public:
    Blake2BHasher() {
        _outputSize = _config.OutputSize;

        _rawConfig = Blake2Builder::ConfigB(_config, nullptr);

        if (!_config.Key.empty()) {
            _key = _config.Key;
        }

        Init();
    }

    explicit Blake2BHasher(const Blake2BConfig& config): _config(config) {
        _outputSize = _config.OutputSize;

        _rawConfig = Blake2Builder::ConfigB(_config, nullptr);

        if (!_config.Key.empty()) {
            _key = _config.Key;
        }

        Init();
    }

    ~Blake2BHasher() override {
        delete[] _rawConfig;
    }

    void Init() override {
        _core.Initialize(_rawConfig);

        if (!_key.empty()) {
            _core.HashCore(_key.data(), 0, _key.size());
        }
    }

    void Update(const uint8_t* data, size_t start, size_t count) override {
        if (data == nullptr && count != 0)
            return;

        _core.HashCore(data, start, count);
    }

    uint8_t* Finish(size_t& length) override {
        std::vector<uint8_t> full = _core.HashFinal();

        length = static_cast<size_t>(_outputSize);

        uint8_t* result = new uint8_t[length];

        std::copy(full.begin(), full.begin() + length, result);

        return result;
    }

    int GetOutputSize() const {
        return _outputSize;
    }

    const Blake2BConfig& GetConfig() const {
        return _config;
    }
};
