#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Frontend/Scanner.h>
#include <Timer.h>

typedef struct _Options {
    bool print_tokens;
    const char *filename;
    const char *output_filename;
} Options;

void print_help(const char *exec) {
    printf("Usage: %s [filename]\n", exec);
}

int parse_args(int argc, char **argv, Options *options) {
    Options result = {0};
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

int main(int argc, char **argv) {
    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    Options options = {0};
    if (parse_args(argc, argv, &options)) {
        return 0;
    }

    Timer timer2 = timer_create();
    Timer timer = timer_create();

    /*FILE* file = fopen("test2.rw", "rb");
    if (file == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);*/

    /*FILE* file = fopen("test2.rw", "rb");
    if (file == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }*/

    /*printf("Bytes read: %#lx\n", bytes_read);

    fclose(file);

    printf("Read file: %f\n", timer_elapsed(&timer));
    timer_reset(&timer);*/

    //Scanner *scanner = scanner_init(file_contents, file_size);

    init_keywords_table();

    uint64 token_count;
    Token *tokens = scan(argv[1], &token_count);

    fprintf(stdout, "Scan: %f\n", timer_elapsed(&timer));
    
    timer_reset(&timer);

    if (options.print_tokens) {
        FILE *out_file = stdout;
        if (options.output_filename != NULL) {
            out_file = fopen(options.output_filename, "wb");
            if (out_file == NULL) {
                printf("Failed to open file (%s) for writing!\n", options.output_filename);
                return -1;
            }
        }
        
        for (uint64 i = 0; i < token_count; i++) {
            fprintf(out_file, "[%s: %.*s]\n", token_type_names[(uint16)tokens[i].type], (int)tokens[i].length, tokens[i].token);
        }

        if (options.output_filename != NULL) {
            fclose(out_file);
        }
    }

    fprintf(stdout, "Output tokens: %f\n", timer_elapsed(&timer));
    fprintf(stdout, "Token count: %llu\n", token_count);
    fprintf(stdout, "Time: %12f\n", timer_elapsed(&timer2));
    return 0;
}
