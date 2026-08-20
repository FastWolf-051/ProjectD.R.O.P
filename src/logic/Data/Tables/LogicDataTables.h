#pragma once

#include <array>

#include "LogicDataTable.h"
#include "../../../Titan/CSV/CSVNode.h"
#include "../Core/GlobalID.h"

class LogicDataTables {
public:
    static constexpr int TABLE_COUNT = 29;

private:
    inline static std::array<LogicDataTable*, TABLE_COUNT> _tables{};

public:

    static void Init() {
        _tables.fill(nullptr);
    }

    static void InitDataTable(CSVNode* node, int index) {
        if (index < 0 || index >= TABLE_COUNT)
            return;

        if (_tables[index] != nullptr) {
            _tables[index]->SetTable(
                node->GetTable()
            );
        }
        else {
            switch (index) {
                /*
                case 23:
                    _tables[index] =
                        new LogicCardDataTable(
                            node->GetTable(),
                            index
                        );
                    break;
                */

                default:
                    _tables[index] = new LogicDataTable(node->GetTable(), index);
                    break;
            }
        }
    }

    static void CreateReferences() {
        for (int i = 0; i < TABLE_COUNT; ++i) {
            if (_tables[i] != nullptr) {
                _tables[i]->CreateReferences();
            }
        }
    }

    static LogicDataTable* GetTable(int tableIndex) {
        if (tableIndex < 0 || tableIndex >= TABLE_COUNT)
            return nullptr;

        return _tables[tableIndex];
    }

    static LogicData* GetDataById(int globalId) {
        int tableIndex =
            GlobalID::GetClassID(globalId) - 1;

        if (tableIndex >= 0 &&
            tableIndex < TABLE_COUNT &&
            _tables[tableIndex] != nullptr) {

            return _tables[tableIndex]->GetItemById(globalId);
        }

        return nullptr;
    }

    static LogicData* GetDataById(int globalId, int dataType) {
        LogicData* data = GetDataById(globalId);

        if (data == nullptr)
            return nullptr;

        if (data->GetDataType() != dataType)
            return nullptr;

        return data;
    }

    static LogicData* GetDataByName(const std::string& name, int dataType, LogicData* caller = nullptr) {
        if (dataType < 0 ||
            dataType >= TABLE_COUNT ||
            _tables[dataType] == nullptr) {
            return nullptr;
        }

        return _tables[dataType]->GetDataByName(name, caller);
    }
};