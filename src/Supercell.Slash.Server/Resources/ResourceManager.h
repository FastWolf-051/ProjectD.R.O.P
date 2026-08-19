#pragma once

#include "../../Supercell.Slash.Logic/Data/Resources/LogicResources.h"
#include "../../Supercell.Slash.Logic/Data/Tables/LogicDataTables.h"
#include "../../Supercell.Slash.Titan/CSV/CSVNode.h"

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