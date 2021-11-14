#include <Config.hh>
#include <Instrumentor.hh>
#include <version.h>

#include <stdio.h>
#include <string.h>

void print_help(const char *exec) {
    printf("Usage: %s [filename]\n", exec);
}

void print_version() {
    printf(R"(Rowan compiler version %d.%d.%d-%s.%d_%llu
Built %s
)", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_MOD, VERSION_MOD_VER, version_timecode, version_time);
}

int parse_args(int argc, char **argv, Options *options) {
    PROFILE_FUNC();
    Options result = {0, 0, 0};
    for (int i = 0; i < argc; i++) {
        // @TODO: Use some sort of hash table to figure out what option is here more quickly?
        if (strcmp(argv[i], "--version") == 0) {
            printf("version\n");
            print_version();
            return 1;
        } else if (strcmp(argv[i], "--print-tokens") == 0) {
            result.print_tokens = true;
        } else if (strcmp(argv[i], "-o") == 0) {
            printf("output\n");
            result.output_filename = argv[i+1];
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("command help\n");
            print_help(argv[0]);
        } else {
            result.filename = argv[i];
        }
    }
    if (result.filename == 0) {
        print_help(argv[0]);
        return 1;
    }
    *options = result;
    return 0;
}
