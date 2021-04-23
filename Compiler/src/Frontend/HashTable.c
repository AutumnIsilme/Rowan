#include <Frontend/HashTable.h>

#include <stdlib.h>
/*
HashTable *hash_table_create(uint8 initial_capacity_power, uint64 item_base_size) {
    const uint64 initial_capacity = 2 << initial_capacity_power;
    const uint64 item_size = alignof(struct{uint8 a[item_base_size + 1 + sizeof(uint64)]});
    HashTable *table = malloc(sizeof(HashTable) + (item_size + 1) * (initial_capacity + initial_capacity_power));
    table->capacity = initial_capacity;
    // One extra byte for the 
    table->item_base_size = item_base_size;
    table->item_size = item_size;
    table->probe_limit = initial_capacity_power;
    table->entry_count = 0;
    return table;
}*/
/*
void hash_table_destroy(HashTable *table) {
    free(table);
}

void hash_table_add(HashTable *table, uint64 hash, void* entry) {
    uint8 probe_count = 0;
    uint64 index = hash & (table->capacity - 1);
    
}

void *hash_table_get(HashTable *table, uint64 hash) {
    uint8 probe_count = 0;
    uint64 index = hash & (table->capacity - 1);
    //uint64 ptr_index = 
    return NULL;
}
*/