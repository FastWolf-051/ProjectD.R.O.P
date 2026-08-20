#pragma once

#include "../../logic/Data/Resources/LogicResources.h"
#include "../../logic/Data/Tables/LogicDataTables.h"
#include "../../titan/CSV/CSVNode.h"

class ResourceManager {
public:
    static void Init() {
        LoadGameResources();
    }

private:
    static void LoadGameResources() {
        LogicDataTables::Init();

        LogicDataTableResource** resources = LogicResources::CreateDataTableResourcesArray();

        int count = LogicDataTables::TABLE_COUNT;

        for (int i = 0; i < count; ++i) {
            LogicDataTableResource* resource = resources[i];

            if (resource == nullptr) continue;

            const char* fileName = resource->GetFileName();

            CSVNode node(fileName);

            LogicResources::Load(resources, i, &node);
        }

        delete[] resources;
    }
};