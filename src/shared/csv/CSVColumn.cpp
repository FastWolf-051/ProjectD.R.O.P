#include "CSVColumn.h"

#include <cstring>

#include "../utils/debug/Debugger.h"

CSVColumn::CSVColumn(int type, int size) {
    _type = type;

    _stringValues = nullptr;
    _integerValues = nullptr;
    _booleanValues = nullptr;

    _stringSize = 0;
    _integerSize = 0;
    _booleanSize = 0;

    _stringCapacity = 0;
    _integerCapacity = 0;
    _booleanCapacity = 0;

    switch (type) {
        case 0:
            _stringCapacity = size;
            _stringValues = new char*[size];
            break;

        case 1:
            _integerCapacity = size;
            _integerValues = new int[size];
            break;

        case 2:
            _booleanCapacity = size;
            _booleanValues = new unsigned char[size];
            break;

        default:
            Debugger::Error("Invalid CSVColumn type (%d)", type);
            break;
    }
}

CSVColumn::~CSVColumn() {
    if (_stringValues != nullptr) {
        for (int i = 0; i < _stringSize; i++) {
            delete[] _stringValues[i];
        }

        delete[] _stringValues;
    }

    delete[] _integerValues;
    delete[] _booleanValues;
}

void CSVColumn::AddStringValue(const char* value) {
    if (_stringSize >= _stringCapacity) {
        return;
    }

    if (value == nullptr) {
        _stringValues[_stringSize++] = nullptr;
        return;
    }

    int length = strlen(value);

    char* stringValue = new char[length + 1];

    memcpy(stringValue, value, length);

    stringValue[length] = '\0';

    _stringValues[_stringSize++] = stringValue;
}

void CSVColumn::AddIntegerValue(int value) {
    if (_integerSize >= _integerCapacity) {
        return;
    }

    _integerValues[_integerSize++] = value;
}

void CSVColumn::AddBooleanValue(bool value) {
    if (_booleanSize >= _booleanCapacity) {
        return;
    }

    _booleanValues[_booleanSize++] =
        value ? 1 : 0;
}

void CSVColumn::SetIntegerValue(int value, int idx) {
    _integerValues[idx] = value;
}

void CSVColumn::SetBooleanValue(unsigned char value, int idx) {
    _booleanValues[idx] = value;
}

void CSVColumn::SetStringValue(const char* value, int idx) {
    delete[] _stringValues[idx];

    if (value == nullptr) {
        _stringValues[idx] = nullptr;
        return;
    }

    int length = strlen(value);

    _stringValues[idx] = new char[length + 1];

    memcpy(_stringValues[idx], value, length);

    _stringValues[idx][length] = '\0';
}

const char* CSVColumn::GetStringValue(int idx) {
    return _stringValues[idx];
}

int CSVColumn::GetIntegerValue(int idx) {
    int value = _integerValues[idx];

    if (value != 0x7FFFFFFF) {
        return value;
    }

    return 0;
}

bool CSVColumn::GetBooleanValue(int idx) {
    return _booleanValues[idx] == 1;
}

void CSVColumn::AddEmptyValue() {
    switch (_type) {
        case 0:
            AddStringValue("");
            break;
        case 1:
            AddIntegerValue(0x7FFFFFFF);
            break;
        case 2:
            AddBooleanValue(2);
            break;
    }
}

int CSVColumn::GetArraySize(int startOffset, int endOffset) {
    switch (_type) {
        default:
            for (int i = endOffset - 1; i + 1 > startOffset; i--) {
                if (_stringValues[i] != nullptr &&
                    strlen(_stringValues[i]) > 0) {
                    return i - startOffset + 1;
                }
            }
            break;

        case 1:
            for (int i = endOffset - 1; i + 1 > startOffset; i--) {
                if (_integerValues[i] != 0x7FFFFFFF) {
                    return i - startOffset + 1;
                }
            }
            break;

        case 2:
            for (int i = endOffset - 1; i + 1 > startOffset; i--) {
                if (_booleanValues[i] != 0x2) {
                    return i - startOffset + 1;
                }
            }
            break;
    }

    return 0;
}

int CSVColumn::GetSize() {
    switch (_type) {
        case 0:
            return _stringSize;
        case 1:
            return _integerSize;
        case 2:
            return _booleanSize;
        default:
            return 0;
    }
}

int CSVColumn::GetType() {
    return _type;
}