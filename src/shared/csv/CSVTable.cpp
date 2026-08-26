#include "CSVTable.h"

#include <cstring>
#include <cstdlib>

#include "CSVColumn.h"
#include "CSVNode.h"
#include "CSVRow.h"

#include "../utils/debug/Debugger.h"

CSVTable::CSVTable(CSVNode* node, int size) {
    _node = node;
    _size = size;

    _columnNameList = nullptr;
    _columnList = nullptr;
    _rowList = nullptr;

    _columnNameCount = 0;
    _columnCount = 0;
    _rowCount = 0;

    _columnNameCapacity = size;
    _columnCapacity = size;
    _rowCapacity = size;

    if (_columnNameCapacity > 0) {
        _columnNameList = new char*[_columnNameCapacity];
    }

    if (_columnCapacity > 0) {
        _columnList = new CSVColumn*[_columnCapacity];
    }

    if (_rowCapacity > 0) {
        _rowList = new CSVRow*[_rowCapacity];
    }
}

CSVTable::~CSVTable() {
    if (_columnNameList != nullptr) {
        for (int i = 0; i < _columnNameCount; i++) {
            delete[] _columnNameList[i];
        }

        delete[] _columnNameList;
    }

    if (_columnList != nullptr) {
        for (int i = 0; i < _columnCount; i++) {
            delete _columnList[i];
        }

        delete[] _columnList;
    }

    if (_rowList != nullptr) {
        for (int i = 0; i < _rowCount; i++) {
            delete _rowList[i];
        }

        delete[] _rowList;
    }
}

void CSVTable::AddColumn(const char* name) {
    if (_columnNameCount >= _columnNameCapacity) {
        return;
    }

    int length = strlen(name);

    _columnNameList[_columnNameCount] = new char[length + 1];

    memcpy(_columnNameList[_columnNameCount], name, length);

    _columnNameList[_columnNameCount][length] = '\0';

    _columnNameCount++;
}

void CSVTable::AddColumnType(int type) {
    if (_columnCount >= _columnCapacity) {
        return;
    }

    _columnList[_columnCount++] = new CSVColumn(type, _size);
}

void CSVTable::AddAndConvertValue(const char* value, int idx) {
    CSVColumn* column = _columnList[idx];

    if (value != nullptr && value[0] != '\0') {
        switch (column->GetType()) {
            case 0:
                column->AddStringValue(value);
                break;

            case 1:
                column->AddIntegerValue(atoi(value));
                break;

            case 2: {
                bool booleanValue = false;

                if (strcmp(value, "true") == 0 ||
                    strcmp(value, "True") == 0 ||
                    strcmp(value, "TRUE") == 0) {
                    booleanValue = true;
                }
                else if (strcmp(value, "false") != 0 &&
                        strcmp(value, "False") != 0 &&
                        strcmp(value, "FALSE") != 0) {
                    Debugger::Print(
                        "CSVTable::addAndConvertValue invalid value '%s' in Boolean column '%s', %s",
                        value,
                        _columnNameList[idx],
                        GetFileName()
                    );
                }

                column->AddBooleanValue(booleanValue);

                break;
            }
        }
    }
    else {
        column->AddEmptyValue();
    }
}

const char* CSVTable::GetFileName() {
    return _node->GetName();
}

const char* CSVTable::GetColumnName(int idx) {
    return _columnNameList[idx];
}

int CSVTable::GetColumnCount() {
    return _columnNameCount;
}

const char* CSVTable::GetValueAt(int columnIdx, int idx) {
    if (columnIdx != -1) {
        return _columnList[columnIdx]->GetStringValue(idx);
    }

    return "";
}

const char* CSVTable::GetValue(const char* name, int idx) {
    return GetValueAt(GetColumnIndexByName(name), idx);
}

int CSVTable::GetColumnIndexByName(const char* name) {
    for (int i = 0; i < _columnNameCount; i++) {
        if (strcmp(_columnNameList[i], name) == 0) {
            return i;
        }
    }

    return -1;
}

int CSVTable::GetIntegerValueAt(int columnIdx, int idx) {
    if (columnIdx != -1) {
        return _columnList[columnIdx]->GetIntegerValue(idx);
    }

    return 0;
}

int CSVTable::GetIntegerValue(const char* name, int idx) {
    return GetIntegerValueAt(GetColumnIndexByName(name), idx);
}

bool CSVTable::GetBooleanValueAt(int columnIdx, int idx) {
    if (columnIdx != -1) {
        return _columnList[columnIdx]->GetBooleanValue(idx);
    }

    return false;
}

bool CSVTable::GetBooleanValue(const char* name, int idx) {
    return GetBooleanValueAt(GetColumnIndexByName(name), idx);
}

CSVRow* CSVTable::GetRowAt(int idx) {
    return _rowList[idx];
}

void CSVTable::AddRow(CSVRow* row) {
    if (_rowCount >= _rowCapacity) {
        return;
    }

    _rowList[_rowCount++] = row;
}

int CSVTable::GetColumnRowCount() {
    if (_columnCount == 0) {
        return 0;
    }

    return _columnList[0]->GetSize();
}

int CSVTable::GetColumnType(int idx) {
    return _columnList[idx]->GetType();
}

int CSVTable::GetRowCount() {
    return _rowCount;
}

int CSVTable::GetArraySizeAt(CSVRow* row, int columnIdx) {
    if (_rowCount > 0) {
        int rowIdx = -1;

        for (int i = 0; i < _rowCount; i++) {
            if (_rowList[i] == row) {
                rowIdx = i;
                break;
            }
        }

        if (rowIdx != -1) {
            CSVColumn* column = _columnList[columnIdx];

            int startOffset = _rowList[rowIdx]->GetRowOffset();

            int endOffset = rowIdx + 1 >= _rowCount
                ? column->GetSize()
                : _rowList[rowIdx + 1]->GetRowOffset();

            return column->GetArraySize(startOffset, endOffset);
        }
    }

    return 0;
}

void CSVTable::SetStringValueAt(const char* value, int cIdx, int idx) {
    _columnList[cIdx]->SetStringValue(value, idx);
}

void CSVTable::CreateRow() {
    AddRow(new CSVRow(this));
}

void CSVTable::ColumnNamesLoaded() {
    // nothing here
}

void CSVTable::ValidateColumnTypes() {
    if (_columnNameCount != _columnCount) {
        Debugger::Print(
            "Column name count %d, column type count %d, file %s",
            _columnNameCount,
            _columnCount,
            GetFileName()
        );
    }
}