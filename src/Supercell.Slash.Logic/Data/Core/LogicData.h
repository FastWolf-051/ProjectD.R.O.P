#pragma once

#include "../Tables/LogicDataTable.h"
#include "../../../Supercell.Slash.Titan/CSV/CSVRow.h"
#include "GlobalID.h"

class LogicData {
protected:
    int _globalId;

    CSVRow* _row;
    LogicDataTable* _table;
public:
    LogicData(CSVRow* row, LogicDataTable* table) {
        _row = row;
        _table = table;
        
        _globalId = GlobalID::CreateGlobalID(static_cast<int>(table->GetTableIndex()) + 1,table->GetItemCount())
    }

    virtual void CreateReferences() {}

    void SetCSVRow(CSVRow* row) {
        _row = row;
    }

    int GetGlobalID() const {
        return _globalId;
    }

    int GetInstanceID() const {
        return GlobalID::GetInstanceID(_globalId);
    }

    std::string GetName() const {
        return _row->GetName();
    }

    int GetDataType() const {
        return _table->GetTableIndex();
    }
    
    virtual ~LogicData() = default;
};
