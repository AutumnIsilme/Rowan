#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Frontend/Scanner.hh>
#include <Timer.h>
#include <Instrumentor.hh>

struct Options {
    bool print_tokens;
    const char *filename;
    const char *output_filename;
};

void print_help(const char *exec) {
    printf("Usage: %s [filename]\n", exec);
}

int parse_args(int argc, char **argv, Options *options) {
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

int main(int argc, char **argv) {
    PROFILE_BEGIN_SESSION("Run", "rowan-run.json");
	PROFILE_FUNC();

    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    Options options = {0, 0, 0};
    if (parse_args(argc, argv, &options)) {
        return 0;
    }

    Timer timer2 = timer_create();
    Timer timer = timer_create();

    init_keywords_table();

    TokenView token_view = scan(argv[1]);

    fprintf(stderr, "Scan: %f\n", timer_elapsed(&timer));
    
    timer_reset(&timer);

    if (options.print_tokens) {
        PROFILE_SCOPE("main::output_tokens");
        FILE *out_file = stderr;
        if (options.output_filename != NULL) {
            out_file = fopen(options.output_filename, "wb");
            if (out_file == NULL) {
                printf("Failed to open file (%s) for writing!\n", options.output_filename);
                return -1;
            }
        }
        
        Token *tokens = token_view.tokens;
        for (uint64 i = token_view.start; i < token_view.start + token_view.count; i++) {
            fprintf(out_file, "[%s: %.*s]\n", token_type_names[(uint16)tokens[i].type], (int)tokens[i].length, tokens[i].token);
        }

        if (options.output_filename != NULL) {
            fclose(out_file);
        }
    }

    fprintf(stderr, "Output tokens: %f\n", timer_elapsed(&timer));
    fprintf(stderr, "Token count: %llu\n", token_view.count);
    fprintf(stderr, "Time: %12f\n", timer_elapsed(&timer2));

    PROFILE_END_SESSION();
    return 0;
}
