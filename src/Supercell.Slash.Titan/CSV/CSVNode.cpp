#include "CSVNode.h"

#include <cstring>
#include <cstdlib>
#include <strings.h>

#include "CSVTable.h"

#include "../Debug/Debugger.h"

CSVNode::CSVNode(char** lines, int lineCount, const char* fileName) {
    _name = nullptr;
    _table = nullptr;

    SetName(fileName);

    Load(lines, lineCount);
}

CSVNode::~CSVNode() {
    delete[] _name;
    delete _table;
}

void CSVNode::SetName(const char* name) {
    delete[] _name;

    if (name == nullptr) {
        _name = nullptr;
        return;
    }

    int length = strlen(name);

    _name = new char[length + 1];

    memcpy(_name, name, length);

    _name[length] = '\0';
}

const char* CSVNode::GetName() {
    return _name;
}

CSVTable* CSVNode::GetTable() {
    return _table;
}

int CSVNode::ParseLine(const char* line, char*** fields) {
    int capacity = 8;
    int count = 0;

    char** result = new char*[capacity];

    bool inQuote = false;

    int fieldCapacity = 64;
    int fieldLength = 0;

    char* field = new char[fieldCapacity];

    for (int i = 0;; i++) {
        char currentCharacter = line[i];

        if (currentCharacter == '"') {
            if (inQuote) {
                if (line[i + 1] == '"') {
                    i++;
                }
                else {
                    inQuote = false;
                }
            }
            else {
                inQuote = true;
            }

            continue;
        }

        if (currentCharacter == ',' && !inQuote) {
            field[fieldLength] = '\0';

            if (count >= capacity) {
                capacity *= 2;

                char** temporary = new char*[capacity];

                memcpy(temporary, result, sizeof(char*) * count);

                delete[] result;

                result = temporary;
            }

            result[count++] = field;

            fieldCapacity = 64;
            fieldLength = 0;

            field = new char[fieldCapacity];

            continue;
        }

        if (currentCharacter == '\0') {
            field[fieldLength] = '\0';

            if (count >= capacity) {
                capacity *= 2;

                char** temporary = new char*[capacity];

                memcpy(temporary, result, sizeof(char*) * count);

                delete[] result;

                result = temporary;
            }

            result[count++] = field;

            break;
        }

        if (fieldLength + 1 >= fieldCapacity) {
            fieldCapacity *= 2;

            char* temporary = new char[fieldCapacity];

            memcpy(temporary, field, fieldLength);

            delete[] field;

            field = temporary;
        }

        field[fieldLength++] = currentCharacter;
    }

    *fields = result;

    return count;
}

void CSVNode::Load(char** lines, int lineCount) {
    delete _table;

    _table = new CSVTable(this, lineCount);

    if (lineCount < 2) {
        return;
    }

    char** columnNames = nullptr;

    int columnNameCount = ParseLine(lines[0], &columnNames);

    char** columnTypes = nullptr;

    int columnTypeCount = ParseLine(lines[1], &columnTypes);

    for (int i = 0; i < columnNameCount; i++) {
        _table->AddColumn(columnNames[i]);
    }

    for (int i = 0; i < columnTypeCount; i++) {
        int columnType = -1;

        if (columnTypes[i] != nullptr && columnTypes[i][0] != '\0') {
            if (strcasecmp(columnTypes[i], "string") == 0) {
                columnType = 0;
            }
            else if (strcasecmp(columnTypes[i], "int") == 0) {
                columnType = 1;
            }
            else if (strcasecmp(columnTypes[i], "boolean") == 0) {
                columnType = 2;
            }
            else {
                Debugger::Print(
                    "Invalid column type '%s', column name %s, file %s. Expecting: int/string/boolean.",
                    columnTypes[i],
                    columnNames[i],
                    _name
                );
            }
        }

        _table->AddColumnType(columnType);
    }

    _table->ValidateColumnTypes();

    if (lineCount > 2) {
        for (int i = 2; i < lineCount; i++) {
            char** values = nullptr;

            int valueCount = ParseLine(lines[i], &values);

            if (valueCount > 0) {
                if (values[0] != nullptr && values[0][0] != '\0') {
                    _table->CreateRow();
                }

                for (int j = 0; j < valueCount; j++) {
                    if (j < _table->GetColumnCount()) {
                        _table->AddAndConvertValue(values[j], j);
                    }
                }
            }

            for (int j = 0; j < valueCount; j++) {
                delete[] values[j];
            }

            delete[] values;
        }
    }

    for (int i = 0; i < columnNameCount; i++) {
        delete[] columnNames[i];
    }

    delete[] columnNames;

    for (int i = 0; i < columnTypeCount; i++) {
        delete[] columnTypes[i];
    }

    delete[] columnTypes;
}