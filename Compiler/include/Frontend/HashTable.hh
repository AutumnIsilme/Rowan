#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <Common.h>
#include <Frontend/Token.h>

#include <stdlib.h>

template<typename T>
struct TableEntry {
    uint64 hash;
    T *data;
    uint8 present;
    uint8 probe_count;
};

template<typename T>
struct HashTable {
    uint64 capacity;
    uint64 entry_count;
    uint8 probe_limit;

    TableEntry<T> *entries;

    HashTable(uint8 initial_capacity_power);

    ~HashTable();

    int add(TableEntry<T> entry);

    int remove(uint64 hash);

    TableEntry<T> *get(uint64 hash);

    void realloc();

};

#include <Frontend/HashTable.cpp>

#endif /* _SYMBOL_TABLE_H */