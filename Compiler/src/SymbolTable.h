#ifndef SYMBOL_TABLE_H_GUARD
#define SYMBOL_TABLE_H_GUARD

#include <string>
#include <vector>

#include "Types.h"

enum class Type {
    NONE = 0,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    FLOAT32,
    FLOAT64,
    BOOL,
    CHAR,
    STRING,
};

struct SymbolEntry {
    std::string name;
    Type type;
};

struct SymbolTable {
    std::vector<SymbolEntry> entries;
};

#endif /* SYMBOL_TABLE_H_GUARD */