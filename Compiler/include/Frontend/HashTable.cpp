#include <Frontend/HashTable.hh>

#include <stdlib.h>
#include <string.h>

template<typename T>
HashTable<T>::HashTable(uint8 initial_capacity_power) {
    capacity = 2 << initial_capacity_power;
    //const uint64 item_size = alignof(struct{uint8 a[item_base_size + 1 + sizeof(uint64)]});
    entries = (TableEntry<T>*)calloc(capacity + initial_capacity_power, sizeof(TableEntry<T>));
    probe_limit = initial_capacity_power;
    entry_count = 0;
}

template<typename T>
HashTable<T>::~HashTable() {
    if (entries) free(entries);
}

template<typename T>
int HashTable<T>::add(TableEntry<T> entry) {
    entry.probe_count = 0;
    uint64 index = entry.hash & (capacity - 1);
    uint64 probe = 0;
    int running = 1;
    while (running) {
        while (entries[index + probe].present &&
                entries[index + probe].hash != entry.hash &&
                entries[index + probe].probe_count >= probe &&
                probe < probe_limit) {
            probe++;
        }
        if (probe >= probe_limit) {
            // Reached probe limit, so extend table and try again
            realloc();
            probe = 0;
            index = entry.hash & (capacity - 1);
            continue;
            //printf("Would now reallocate, and table is broken.\n");
        }
        if (entries[index + probe].hash == entry.hash) {
            // @TODO: I don't quite know what to do here.
            return 1;
        }

        TableEntry<T> tmp = entries[index + probe];
        entries[index + probe] = entry;
        entry = tmp;

        entries[index + probe].probe_count = probe;

        if (entry.present == 0) {
            running = 0;
        }

        probe = entry.probe_count;
        index = entry.hash & (capacity - 1);
    }
    entry_count += 1;

    // Check load factor and reallocate if over 50%
    if (entry_count > capacity >> 1) {
        realloc();
    }
    return 0;
}

template<typename T>
TableEntry<T> *HashTable<T>::get(uint64 hash) {
    uint8 probe = 0;
    uint64 index = hash & (capacity - 1);
    while (entries[index + probe].hash != hash &&
            probe < probe_limit) {
        probe++;
    }
    if (entries[index + probe].hash != hash)
        return NULL;
    else
        return &entries[index + probe];
}

template<typename T>
void HashTable<T>::realloc() {
    TableEntry<T> *new_entries = (TableEntry<T>*)calloc((capacity << 1) + probe_limit + 1, sizeof(TableEntry<T>));
    capacity <<= 1;
    probe_limit++;
    TableEntry<T> *old_entries = entries;
    entries = new_entries;

    for (uint64 i = 0; i < capacity >> 1; i++) {
        if (old_entries[i].present) {
            add(old_entries[i]);
        }
    }
    free(old_entries);
}
