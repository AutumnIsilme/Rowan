#include <Common.h>

struct FileReadResult {
    char* buffer;
    uint64 size;
    FileReadResult(char* buffer, uint64 size)
        : buffer(buffer), size(size) {}
};
FileReadResult read_file(const char* filename);
void free_file(FileReadResult file);
