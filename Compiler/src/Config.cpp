#include <Config.hh>
#include <Instrumentor.hh>

#include <stdio.h>
#include <string.h>

void print_help(const char *exec) {
    printf("Usage: %s [filename]\n", exec);
}

int parse_args(int argc, char **argv, Options *options) {
    PROFILE_FUNC();
    Options result = {0, 0, 0};
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--print-tokens") == 0) {
            result.print_tokens = true;
        } else if (strcmp(argv[i], "-o") == 0) {
            result.output_filename = argv[i+1];
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
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