#pragma once

#include <vector>

#include "LogicDataTableResource.h"
#include "../Tables/LogicDataTables.h"
#include "../../../Supercell.Slash.Titan/CSV/CSVNode.h"
#include "../../../Supercell.Slash.Titan/Debug/Debugger.h"

class LogicResources {
public:
    static std::vector<LogicDataTableResource> CreateDataTableResourcesArray() {
        std::vector<LogicDataTableResource> resources;

        resources.reserve(LogicDataTables::TABLE_COUNT);

        return resources;
    }

    static void Load(std::vector<LogicDataTableResource>& resources, int idx, CSVNode* node) {
        LogicDataTableResource& resource = resources[idx];

        switch (resource.GetTableType()) {
            case 0:
                LogicDataTables::InitDataTable(node, resource.GetTableIndex());
                break;

            default:
                Debugger::Error("LogicResources::Load(): invalid resource type");
                break;
        }

        if (static_cast<int>(resources.size()) - 1 == idx) {
            LogicDataTables::CreateReferences();
        }
    }
};
