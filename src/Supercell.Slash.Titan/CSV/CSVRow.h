#pragma once

class CSVTable;

class CSVRow {
private:
    CSVTable* _table;
    int _rowOffset;

public:
    CSVRow(CSVTable* table);

    const char* GetValueAt(int columnIdx, int idx);
    int GetLongestArraySize();
    int GetColumnCount();
    int GetArraySizeAt(int idx);

    const char* GetValue(const char* name, int idx);
    const char* GetClampedValue(const char* name, int idx);

    int GetColumnIndexByName(const char* name);

    int GetIntegerValueAt(int cIdx, int idx);
    int GetIntegerValue(const char* name, int idx);
    int GetClampedIntegerValue(const char* name, int idx);

    bool GetBooleanValueAt(int cIdx, int idx);
    bool GetBooleanValue(const char* name, int idx);
    bool GetClampedBooleanValue(const char* name, int idx);

    int GetArraySize(const char* column);

    int GetRowOffset();
    int GetRowCount();

    const char* GetName();

    CSVTable* GetTable();

    void SetStringValueAt(const char* value, int cIdx, int idx);
};