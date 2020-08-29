/*#include <cstdio>
#include <fstream>
#include <string.h>*/

#include <stdio.h>
#include <string.h>

#include "Scanner.h"
#include "Timer.h"

int main(int argc, char **argv) {
    #ifndef NDEBUG
    printf("Hello, World!\n");
    #endif

    Timer timer2 = timer_create();
    Timer timer = timer_create();

    struct timeval tv;
    gettimeofday(&tv, NULL);

    FILE* file = fopen("test_2_4M_lines.rw", "rb");

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* file_contents = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(file_contents, sizeof(char), fileSize, file);
    file_contents[bytesRead] = '\0';

    fclose(file);

    struct timeval tv2;
    gettimeofday(&tv2, NULL);

    printf("Read file: %f\n", timer_elapsed(&timer));
    timer_reset(&timer);

    Scanner *scanner = scanner_init(file_contents);

    printf("Init: %f\n", timer_elapsed(&timer));
    timer_reset(&timer);

    //printf("%zu\n", Lexer_Old.tokens->size());
    //Token *first = token_create(TT_AMPERSAND, 0, 0, 0, 0);
    Token t = (Token){TT_AMPERSAND, 0, 0, 0, 0};
    while (t.type != TT_EOF) {
        //printf("Making token!");
        t = scanner_next(scanner);
        //printf("Copying to contents!");
        //char* contents = (char*)malloc(t->length+1);
        //memcpy(contents, t->token, t->length);
        //contents[t->length] = '\0';
        //printf("End!");
        //printf("[%s: %s]\n", token_type_names[(u16)t->type], contents);
    }

    printf("Output tokens: %f\n", timer_elapsed(&timer));
    printf("Total: %f\n", timer_elapsed(&timer2));
    return 0;
}

struct test {
    int a;
    char b;
};

struct test test_create(int a, char b) {
    return (struct test){a, b};
}