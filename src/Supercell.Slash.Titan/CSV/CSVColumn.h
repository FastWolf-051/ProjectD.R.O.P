#pragma once

class CSVColumn {
private:
    int _type;

    char** _stringValues;
    int* _integerValues;
    unsigned char* _booleanValues;

    int _stringSize;
    int _integerSize;
    int _booleanSize;

    int _stringCapacity;
    int _integerCapacity;
    int _booleanCapacity;

public:
    CSVColumn(int type, int size);
    ~CSVColumn();

    void AddStringValue(const char* value);
    void AddIntegerValue(int value);
    void AddBooleanValue(bool value);

    void SetIntegerValue(int value, int idx);
    void SetBooleanValue(unsigned char value, int idx);
    void SetStringValue(const char* value, int idx);

    const char* GetStringValue(int idx);
    int GetIntegerValue(int idx);
    bool GetBooleanValue(int idx);

    void AddEmptyValue();

    int GetArraySize(int startOffset, int endOffset);
    int GetSize();
    int GetType();
};

enum CSVColumnType {
    STRING = 0,
    INT = 1,
    BOOL = 2
};