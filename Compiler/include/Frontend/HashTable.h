#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <Frontend/Common.h>
#include <Frontend/Token.h>

typedef struct _HashTable {
    uint64 capacity;
    uint64 entry_count;
    uint64 item_base_size;
    uint64 item_size;
    uint8 probe_limit;

    uint8  _unused_0;
    uint16 _unused_1;
    uint32 _unused_2;

    uint8 entries[];
} HashTable;

HashTable *hash_table_create(uint8 initial_capacity_power, uint64 item_size);
void hash_table_destroy(HashTable *table);
void hash_table_add(HashTable *table, uint64 hash, void* entry);
void *hash_table_get(HashTable *table, uint64 hash);

#endif /* _SYMBOL_TABLE_H */