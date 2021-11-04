#include <Common.h>

struct Config {
    bool print_tokens;
    const char *initial_filename;
    const char *output_filename;
};
struct Options {
    bool print_tokens;
    const char *filename;
    const char *output_filename;
};
void print_help(const char *exec);
int parse_args(int argc, char **argv, Options *options);