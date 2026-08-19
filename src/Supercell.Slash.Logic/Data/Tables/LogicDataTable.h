#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Core/LogicData.h"
#include "../../../Supercell.Slash.Titan/CSV/CSVTable.h"
#include "../../../Supercell.Slash.Titan/CSV/CSVRow.h"
#include "../../../Supercell.Slash.Titan/Debug/Debugger.h"

class LogicDataTable {
private:
    int _tableIdx;
    std::string _tableName;
    bool _isLoaded;
protected:
    CSVTable* _table;
    std::vector<LogicData*> _items;
public:
    LogicDataTable() {
        _tableIdx = 0;
        _tableName = "";
        _isLoaded = false;
        _table = nullptr;

        LoadTable();
    }

    virtual ~LogicDataTable() = default;

    void LoadTable() {
        for (int i = 0, j = _table->GetRowCount(); i < j; ++i) {
            LogicData* item = CreateItem(_table->GetRowAt(i));

            if (item != nullptr)
                _items.push_back(item);
        }
    }

    virtual void CreateReferences() {
        if (!_isLoaded) {
            for (LogicData* item : _items) {
                if (item != nullptr)
                    item->CreateReferences();
            }

            _isLoaded = true;
        }
    }

    LogicData* GetItemAt(int index) {
        if (index < 0 || index >= static_cast<int>(_items.size()))
            return nullptr;

        return _items[index];
    }

    virtual LogicData* CreateItem(CSVRow* row) {
        LogicData* item = nullptr;

        switch (_tableIdx) {
            /*
            case 23:
                item = new LogicCardData(row, this);
                break;
            */

            default:
                std::cout << "Invalid data table id: " << _tableIdx << std::endl;
                break;
        }

        return item;
    }

    void SetTable(CSVTable* table) {
        _table = table;

        for (int i = 0; i < static_cast<int>(_items.size()); ++i) {
            if (_items[i] != nullptr) {
                _items[i]->SetCSVRow(
                    _table->GetRowAt(i)
                );
            }
        }
    }

    void SetName(const std::string& name) {
        _tableName = name;
    }

    int GetTableIndex() const {
        return _tableIdx;
    }

    int GetItemCount() const {
        return static_cast<int>(_items.size());
    }

    LogicData* GetItemById(int globalId) {
        int instanceId = GlobalID::GetInstanceID(globalId);

        if (instanceId >= 0 &&
            instanceId < static_cast<int>(_items.size())) {
            return _items[instanceId];
        }

        Debugger::Warning(
            "LogicDataTable.GetItemById() - Instance id out of bounds!"
        );

        return nullptr;
    }

    LogicData* GetDataByName(const std::string& name, LogicData* caller = nullptr) {
        if (!name.empty()) {
            for (LogicData* data : _items) {
                if (data != nullptr &&
                    data->GetName() == name) {
                    return data;
                }
            }

            if (caller != nullptr) {
                char buffer[512];

                std::snprintf(
                    buffer,
                    sizeof(buffer),
                    "CSV row (%s) has an invalid reference (%s)",
                    caller->GetName().c_str(),
                    name.c_str()
                );

                Debugger::Warning(buffer);
            }
        }

        return nullptr;
    }

    const std::string& GetTableName() const {
        return _tableName;
    }
};
