#pragma once

#include <string>

class LogicDataTableResource {
private:
    std::string _fileName;

    int _tableIndex;
    int _type;
public:
    LogicDataTableResource(const std::string& fileName, int tableIndex, int type) {
        _fileName = fileName,
        _tableIndex = tableIndex,
        _type = type
    }

    void Destruct() {
        _fileName.clear();

        _tableIndex = 0;
        _type = 0;
    }

    const std::string& GetFileName() const {
        return _fileName;
    }

    int GetTableIndex() const {
        return _tableIndex;
    }

    int GetTableType() const {
        return _type;
    }
};