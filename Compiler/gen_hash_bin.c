#include <Frontend/Common.h>
#include <Frontend/KeywordList.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SHIFT 7

/*
uint64 hash(const char *str) {
    uint64 h = 0;
    for (uint i = 0; i < strlen(str); i++) {
        h = ROL(h, 2) + str[i];
    }
    return h;
}*/

uint64 fnv_1(const char *data, uint64 length) {
    uint64 hash = 0xcbf29ce484222325UL;
    for (uint64 i = 0; i < length; i++) {
        hash ^= data[i];
        hash *= 0x100000001b3UL;
    }
    return hash;
}

uint64 hashes[KEYWORD_LIST_LEN] = {0};
uint64 lengths[KEYWORD_LIST_LEN] = {0};
//uint64 buckets_count[1<<SHIFT] = {0};
struct TableEntry {
    uint64 hash;
    void *text;
    uint8 types;
    uint8 present;
    uint8 probe_count;
};
struct TableEntry buckets[(1<<SHIFT) + SHIFT] = {0};
uint64 buckets_hashes[1<<SHIFT] = {0};
uint64 buckets_types[1<<SHIFT] = {0};

const int max_probe_count = SHIFT;

int main() {
    printf("%lu\n", sizeof(struct TableEntry));
    for (uint i = 0; i < 1<<SHIFT; i++) {
        buckets_types[i] = TT_NONE;
    }
    for (uint i = 0; i < KEYWORD_LIST_LEN; i++) {
        lengths[i] = strlen(KEYWORD_LIST[i]);
        hashes[i] = fnv_1(KEYWORD_LIST[i], lengths[i]);
        struct TableEntry e = (struct TableEntry){hashes[i], KEYWORD_LIST[i], i, 1, 0};
        // Insert
        uint64 index = hashes[i] & ((1 << SHIFT) - 1);
        uint64 probe = 0;
        int running = 1;
        while (running) {
            while (buckets[index + probe].present &&
                buckets[index + probe].hash != hashes[i] &&
                buckets[index + probe].probe_count >= probe &&
                probe < max_probe_count) {
                //printf("%llu: %d\n", probe, buckets[index + probe].probe_count);
                probe++;
            }
            if (probe >= max_probe_count) {
                printf("Would now reallocate, and table is broken.\n");
            }
            if (buckets[index + probe].hash == hashes[i]) {
                if ()
            }

            //buckets_hashes[index + probe] = hashes[i];
            //buckets_types[index + probe] = i;

            struct TableEntry tmp = buckets[index + probe];
            buckets[index + probe] = e;
            e = tmp;

            buckets[index + probe].probe_count = probe;
            probe = e.probe_count;
            index = e.hash & ((1 << SHIFT) - 1);

            if (e.present == 0) {
                running = 0;
            }
        }
        printf("%8s: %3llu: %llu\n", KEYWORD_LIST[i], hashes[i] & ((1 << SHIFT) - 1), hashes[i]);
    }
    for (uint i = 0; i < (1 << SHIFT) + SHIFT; i++) {
        printf("[%llu: %d, %d, %d]\n", buckets[i].hash, buckets[i].types, buckets[i].present, buckets[i].probe_count);
    }
    return 0;
}
