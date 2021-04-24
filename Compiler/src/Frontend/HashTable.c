#include <Frontend/HashTable.h>

#include <stdlib.h>
#include <string.h>

HashTable *hash_table_create(uint8 initial_capacity_power) {
    const uint64 initial_capacity = 2 << initial_capacity_power;
    //const uint64 item_size = alignof(struct{uint8 a[item_base_size + 1 + sizeof(uint64)]});
    HashTable *table = malloc(sizeof(HashTable));
    table->entries = malloc(sizeof(TableEntry) * (initial_capacity + initial_capacity_power));
    table->capacity = initial_capacity;
    table->probe_limit = initial_capacity_power;
    table->entry_count = 0;
    return table;
}

void hash_table_destroy(HashTable *table) {
    free(table);
}

int hash_table_add(HashTable *table, TableEntry entry) {
    entry.probe_count = 0;
    uint64 index = entry.hash & (table->capacity - 1);
    uint64 probe = 0;
    int running = 1;
    while (running) {
        while (table->entries[index + probe].present &&
                table->entries[index + probe].hash != entry.hash &&
                table->entries[index + probe].probe_count >= probe &&
                probe < table->probe_limit) {
            probe++;
        }
        if (probe >= table->probe_limit) {
            // Reached probe limit, so extend table and try again
            hash_table_realloc(table);
            probe = 0;
            index = entry.hash & (table->capacity - 1);
            continue;
            //printf("Would now reallocate, and table is broken.\n");
        }
        if (table->entries[index + probe].hash == entry.hash) {
            // @TODO: I don't quite know what to do here.
            return 1;
        }

        TableEntry tmp = table->entries[index + probe];
        table->entries[index + probe] = entry;
        entry = tmp;

        table->entries[index + probe].probe_count = probe;

        if (entry.present == 0) {
            running = 0;
        }

        probe = entry.probe_count;
        index = entry.hash & (table->capacity - 1);
    }
    table->entry_count += 1;

    // Check load factor and reallocate if over 50%
    if (table->entry_count > table->capacity >> 1) {
        hash_table_realloc(table);
    }
    return 0;
}

/*
int hash_table_remove(HashTable *table, uint64 hash) {
    // @TODO
    return -1;
}*/

TableEntry *hash_table_get(HashTable *table, uint64 hash) {
    uint8 probe = 0;
    uint64 index = hash & (table->capacity - 1);
    while (table->entries[index + probe].hash != hash &&
            probe < table->probe_limit) {
        probe++;
    }
    if (table->entries[index + probe].hash != hash)
        return NULL;
    else
        return &table->entries[index + probe];
}

void hash_table_realloc(HashTable *table) {
    TableEntry *new_entries = malloc(sizeof(TableEntry) * ((table->capacity << 1) + table->probe_limit + 1));
    table->capacity <<= 1;
    table->probe_limit++;
    TableEntry *old_entries = table->entries;
    table->entries = new_entries;

    for (uint64 i = 0; i < table->capacity >> 1; i++) {
        if (old_entries[i].present) {
            hash_table_add(table, old_entries[i]);
        }
    }
}
