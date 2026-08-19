#pragma once

#include <string>
#include <cstdio>

class GlobalID {
public:
    static int CreateGlobalID(int classId, int instanceId) {
        return 1000000 * classId + instanceId;
    }

    static int GetInstanceID(int globalId) {
        return globalId % 1000000;
    }

    static int GetClassID(int globalId) {
        return globalId / 1000000;
    }

    static std::string ToString(int globalId) {
        char buffer[64];

        std::snprintf(buffer, sizeof(buffer), "GlobalId(%d, %d)",
            GetClassID(globalId), GetInstanceID(globalId)
        );

        return std::string(buffer);
    }
};