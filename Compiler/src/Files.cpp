#include <Files.hh>
#include <stdlib.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

FileReadResult read_file(const char* filename) {
    auto file_handle = CreateFileA((LPCSTR)filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        exit(1);
    }
    auto mapping_handle = CreateFileMappingA(file_handle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (mapping_handle == INVALID_HANDLE_VALUE) {
        exit(1);
    }
    auto file_pointer = MapViewOfFile(mapping_handle, FILE_MAP_READ, 0, 0, 0);
    if (file_pointer == 0) {
        exit(1);
    }
    DWORD file_size_high;
    DWORD file_size_low = GetFileSize(file_handle, &file_size_high);
    CloseHandle(file_handle);
    CloseHandle(mapping_handle);
    FileReadResult result = FileReadResult((char*)file_pointer, (uint64)((((uint64)file_size_high) << 32) | ((uint64)file_size_low)));
    return result;
}

/*FileReadResult read_file(const char* filename) {
    auto file_handle = CreateFileA((LPCSTR)filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        exit(1);
    }
    DWORD file_size_high;
    DWORD file_size_low = GetFileSize(file_handle, &file_size_high);
    uint64 file_size = ((uint64)file_size_high << 32) | file_size_low;
    char* buffer = static_cast<char*>(malloc(file_size));
    auto success = ReadFile(file_handle, static_cast<void*>(buffer), 0, NULL, NULL);
    if (!success) {
        exit(1);
    }
    CloseHandle(file_handle);
    FileReadResult result = FileReadResult((char*)buffer, file_size);
    return result;
}
*/

void free_file(FileReadResult file) {
    UnmapViewOfFile(static_cast<void*>(file.buffer));
}

#else
#include <unistd.h>
#include <sys/mman.h>

FileReadResult read(const char* filename) {
    int file = open(filename, O_RDONLY);
    struct stat s;
    int status = fstat(file, &s);
    if (status == -1) {
        exit(1); // show errno
    }
    uint64 file_size = s.st_size;

    source = (char*)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, file, 0);
    if (source == NULL) {
        exit(1);
    }
    if (madvise(source, file_size, MADV_SEQUENTIAL | MADV_WILLNEED)) {
        exit(1);
    }
    close(file);

    return {
        source,
        file_size
    };
}

void free_file(FileReadResult file) {
    munmap(file.buffer, file.size);
}

#endif