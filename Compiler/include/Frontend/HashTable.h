#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <Frontend/Common.h>
#include <Frontend/Token.h>

typedef struct _TableEntry {
    uint64 hash;
    void *data;
    uint8 present;
    uint8 probe_count;
} TableEntry;

typedef struct _HashTable {
    uint64 capacity;
    uint64 entry_count;
    uint8 probe_limit;

    TableEntry *entries;
} HashTable;

HashTable *hash_table_create(uint8 initial_capacity_power);
void hash_table_destroy(HashTable *table);
int hash_table_add(HashTable *table, TableEntry entry);
int hash_table_remove(HashTable *table, uint64 hash);
TableEntry *hash_table_get(HashTable *table, uint64 hash);
void hash_table_realloc(HashTable *table);

#endif /* _SYMBOL_TABLE_H */