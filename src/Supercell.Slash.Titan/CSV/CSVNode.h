#pragma once

class CSVTable;

class CSVNode {
private:
    char* _name;
    CSVTable* _table;

public:
    CSVNode(char** lines, int lineCount, const char* fileName);
    ~CSVNode();

    void Load(char** lines, int lineCount);
    int ParseLine(const char* line, char*** fields);

    void SetName(const char* name);

    const char* GetName();
    CSVTable* GetTable();
};