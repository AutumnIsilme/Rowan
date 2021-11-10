#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Frontend/Scanner.hh>
#include <Frontend/Parser.hh>
#include <Config.hh>
#include <Error.h>
#include <Timer.h>
#include <Instrumentor.hh>

int main(int argc, char **argv) {
    PROFILE_BEGIN_SESSION("Run", "rowan-run.json");
	//PROFILE_FUNC();

    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    Options options = {0, 0, 0};
    //Config config = parse_args(argc, argv, &options);
    if (parse_args(argc, argv, &options)) {
        return 0;
    }

    Timer timer2 = timer_create();
    Timer timer = timer_create();

    init_symbol_table();

    Scanner token_view = Scanner(options.filename);

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
            fprintf(out_file, "[%s: %.*s]\n", token_type_names[(uint16)tokens[i].kind], (int)tokens[i].length, tokens[i].token);
        }

        if (options.output_filename != NULL) {
            fclose(out_file);
        }
    }

    fprintf(stderr, "Output tokens: %f\n", timer_elapsed(&timer));
    fprintf(stderr, "Token count: %llu\n", token_view.count);
    fprintf(stderr, "Time: %12f\n", timer_elapsed(&timer2));

    //auto parser = Parser(&token_view);
    //fprintf(stderr, "Parser complete.\n");
    //report_error(__FILE__, __LINE__, "aaa", token_view.file_data, parser.temp_toplevel->value.token->offset, parser.temp_toplevel->value.token->length, "Parser: Temp_toplevel error help info thingy");

    PROFILE_END_SESSION();
    return 0;
}
