#include "CSVRow.h"
#include "CSVTable.h"

CSVRow::CSVRow(CSVTable* table) {
    _table = table;
    _rowOffset = table->GetColumnRowCount();
}

const char* CSVRow::GetValueAt(int columnIdx, int idx) {
    return _table->GetValueAt(columnIdx, _rowOffset + idx);
}

int CSVRow::GetLongestArraySize() {
    int longestArraySize = 1;

    for (int i = _table->GetColumnCount() - 1; i > 0; i--) {
        int arraySizeAt = _table->GetArraySizeAt(this, i);

        if (arraySizeAt > longestArraySize) {
            longestArraySize = arraySizeAt;
        }
    }

    return longestArraySize;
}

int CSVRow::GetColumnCount() {
    return _table->GetColumnCount();
}

int CSVRow::GetArraySizeAt(int idx) {
    return _table->GetArraySizeAt(this, idx);
}

const char* CSVRow::GetValue(const char* name, int idx) {
    return _table->GetValue(name, _rowOffset + idx);
}

const char* CSVRow::GetClampedValue(const char* name, int idx) {
    int columnIdx = _table->GetColumnIndexByName(name);

    if (columnIdx != -1) {
        int arraySize = _table->GetArraySizeAt(this, columnIdx);

        if (arraySize >= 1 && arraySize <= idx) {
            idx = arraySize - 1;
        }

        return _table->GetValueAt(columnIdx, _rowOffset + idx);
    }

    return "";
}

int CSVRow::GetColumnIndexByName(const char* name) {
    return _table->GetColumnIndexByName(name);
}

int CSVRow::GetIntegerValueAt(int cIdx, int idx) {
    return _table->GetIntegerValueAt(cIdx, _rowOffset + idx);
}

int CSVRow::GetIntegerValue(const char* name, int idx) {
    return _table->GetIntegerValue(name, _rowOffset + idx);
}

int CSVRow::GetClampedIntegerValue(const char* name, int idx) {
    int columnIdx = _table->GetColumnIndexByName(name);

    if (columnIdx != -1) {
        int arraySize = _table->GetArraySizeAt(this, columnIdx);

        if (arraySize >= 1 && arraySize <= idx) {
            idx = arraySize - 1;
        }

        return _table->GetIntegerValueAt(columnIdx, _rowOffset + idx);
    }

    return 0;
}

bool CSVRow::GetBooleanValueAt(int cIdx, int idx) {
    return _table->GetBooleanValueAt(cIdx, _rowOffset + idx);
}

bool CSVRow::GetBooleanValue(const char* name, int idx) {
    return _table->GetBooleanValue(name, _rowOffset + idx);
}

bool CSVRow::GetClampedBooleanValue(const char* name, int idx) {
    int columnIdx = _table->GetColumnIndexByName(name);

    if (columnIdx != -1) {
        int arraySize = _table->GetArraySizeAt(this, columnIdx);

        if (arraySize >= 1 && arraySize <= idx) {
            idx = arraySize - 1;
        }

        return _table->GetBooleanValueAt(columnIdx, _rowOffset + idx);
    }

    return false;
}

int CSVRow::GetArraySize(const char* column) {
    int columnIndex = GetColumnIndexByName(column);

    if (columnIndex == -1) {
        return 0;
    }

    return _table->GetArraySizeAt(this, columnIndex);
}

int CSVRow::GetRowOffset() {
    return _rowOffset;
}

int CSVRow::GetRowCount() {
    return -1;
}

const char* CSVRow::GetName() {
    return _table->GetValueAt(0, _rowOffset);
}

CSVTable* CSVRow::GetTable() {
    return _table;
}

void CSVRow::SetStringValueAt(const char* value, int cIdx, int idx) {
    _table->SetStringValueAt(value, cIdx, idx);
}