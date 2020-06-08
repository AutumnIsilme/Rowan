#ifndef SYMBOL_TABLE_H_GUARD
#define SYMBOL_TABLE_H_GUARD

#include <string>
#include <vector>

#include "Types.h"

struct SymbolEntry {
    std::string name;
    //Type type
};

struct SymbolTable {
    std::vector<SymbolEntry> entries;
};

#endif /* SYMBOL_TABLE_H_GUARD */