#pragma once

class CSVNode;
class CSVRow;
class CSVColumn;

class CSVTable {
private:
    CSVNode* _node;

    char** _columnNameList;
    CSVColumn** _columnList;
    CSVRow** _rowList;

    int _columnNameCount;
    int _columnCount;
    int _rowCount;

    int _columnNameCapacity;
    int _columnCapacity;
    int _rowCapacity;

    int _size;
public:
    CSVTable(CSVNode* node, int size);
    ~CSVTable();

    void AddColumn(const char* name);
    void AddColumnType(int type);
    void AddAndConvertValue(const char* value, int idx);

    const char* GetFileName();

    const char* GetColumnName(int idx);

    int GetColumnCount();

    const char* GetValueAt(int columnIdx, int idx);
    const char* GetValue(const char* name, int idx);

    int GetColumnIndexByName(const char* name);

    int GetIntegerValueAt(int columnIdx, int idx);
    int GetIntegerValue(const char* name, int idx);

    bool GetBooleanValueAt(int columnIdx, int idx);
    bool GetBooleanValue(const char* name, int idx);

    CSVRow* GetRowAt(int idx);

    void AddRow(CSVRow* row);

    int GetColumnRowCount();
    int GetColumnType(int idx);
    int GetRowCount();

    int GetArraySizeAt(CSVRow* row, int columnIdx);

    void SetStringValueAt(const char* value, int cIdx, int idx);

    void CreateRow();

    void ColumnNamesLoaded();
    void ValidateColumnTypes();
};