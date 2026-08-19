#pragma once

#include <cstdint>
#include "Blake2BConfig.h"
#include "Blake2BTreeConfig.h"
#include "Blake2BCore.h"

class Blake2Builder {
private:
    static Blake2BTreeConfig SequentialTreeConfig() {
        Blake2BTreeConfig config;

        config.IntermediateHashSize = 0;
        config.LeafSize = 0;
        config.FanOut = 1;
        config.MaxHeight = 1;

        return config;
    }

public:
    static uint64_t* ConfigB(
        const Blake2BConfig& config,
        const Blake2BTreeConfig* treeConfig = nullptr
    ) {
        Blake2BTreeConfig sequential;

        if (treeConfig == nullptr) {
            sequential = SequentialTreeConfig();
            treeConfig = &sequential;
        }

        uint64_t* rawConfig = new uint64_t[8]{};

        rawConfig[0] |=
            static_cast<uint32_t>(config.OutputSize);

        if (!config.Key.empty()) {
            rawConfig[0] |=
                static_cast<uint32_t>(
                    config.Key.size()
                ) << 8;
        }

        rawConfig[0] |=
            static_cast<uint32_t>(
                treeConfig->FanOut
            ) << 16;

        rawConfig[0] |=
            static_cast<uint32_t>(
                treeConfig->MaxHeight
            ) << 24;

        rawConfig[0] |=
            static_cast<uint64_t>(
                static_cast<uint32_t>(
                    treeConfig->LeafSize
                )
            ) << 32;

        rawConfig[2] |=
            static_cast<uint32_t>(
                treeConfig->IntermediateHashSize
            ) << 8;

        if (config.Salt.size() >= 16) {
            rawConfig[4] =
                Blake2BCore::BytesToUInt64Public(
                    config.Salt.data(), 0
                );

            rawConfig[5] =
                Blake2BCore::BytesToUInt64Public(
                    config.Salt.data(), 8
                );
        }

        if (config.Personalization.size() >= 16) {
            rawConfig[6] =
                Blake2BCore::BytesToUInt64Public(
                    config.Personalization.data(), 0
                );

            rawConfig[7] =
                Blake2BCore::BytesToUInt64Public(
                    config.Personalization.data(), 8
                );
        }

        return rawConfig;
    }

    static void ConfigBSetNode(
        uint64_t* rawConfig,
        uint8_t depth,
        uint64_t nodeOffset
    ) {
        rawConfig[1] = nodeOffset;

        rawConfig[2] =
            (rawConfig[2] & ~0xFFULL) |
            depth;
    }
};
