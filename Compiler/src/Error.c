#include <Error.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static int error_count;

/*

(Scanner.c line 126) reporting (foo.rw line 16 column 72) Compile Error:
Lexer Error: Unexpected character
sdifhsaiduf˚asd
           ^

*/

void report_error(const char *reporter_filename, uint64 reporter_line, const char *filename, const char *file, uint64 offset, uint64 span, const char *msg_fmt, ...) {
    error_count++;

    uint64 line = 1;
    uint64 column = 0;
    uint64 index = 0;
    while (index < offset) {
        if (file[index] == '\n') {
            line++;
            column = 0;
        } else {
            column++;
        }
        index++;
    }

    va_list fmt_args;
    va_start(fmt_args, msg_fmt);

    fprintf(stderr, "(%s line %llu) reporting (%s line %llu column %llu) Compile Error:\n",
        reporter_filename, reporter_line, filename, line, column);
    vfprintf(stderr, msg_fmt, fmt_args);
    if (msg_fmt[strlen(msg_fmt) - 1] != '\n') fprintf(stderr, "\n");
    
    index = offset - column;
    while (file[index] != '\n') {
        fprintf(stderr, "%c", file[index]);
        index++;
    }
    fprintf(stderr, "\n%*s^", (int)column, "");
    for (uint i = 0; i < span - 1; i++) {
        fprintf(stderr, "^");
    }
    fprintf(stderr, "\n");
}
