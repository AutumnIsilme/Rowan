/*#include <cstdio>
#include <fstream>
#include <string.h>*/

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "Scanner.h"
#include "Timer.h"

int main(int argc, char **argv) {
    printf("Hello, World!\n");

/*
    auto timer2 = Timer();
    auto timer = Timer();*/

    struct timeval tv;
    gettimeofday(&tv, NULL);
    //struct timespec time;
    //timespec_get(&time, TIME_UTC);
    //clock_gettime(_CLOCK_REALTIME, &time);
    

    FILE* file = fopen("test_4M_lines.rw", "rb");

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* file_contents = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(file_contents, sizeof(char), fileSize, file);
    file_contents[bytesRead] = '\0';

    fclose(file);

    struct timeval tv2;
    gettimeofday(&tv2, NULL);

/*    std::string contents;

    {
    std::ifstream in("test.rw", std::ios::in | std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
    }
    else
    {
        printf("Could not open source file: %s", "test.rw"); //Temporary hardcoded file.
        system("PAUSE");
        //exit(2);
    }
    }*/

/*
    printf("Read file: %f\n", timer.elapsed());
    timer.reset();
*/
    Scanner *scanner = scanner_init(file_contents);

  /*  printf("Init: %f\n", timer.elapsed());
    timer.reset();*/

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

    struct timeval tv3;
    gettimeofday(&tv3, NULL);

    unsigned long long delta1 = tv2.tv_usec + tv2.tv_sec * 1000000 - tv.tv_usec - tv.tv_sec * 1000000;
    unsigned long long delta2 = tv3.tv_usec + tv3.tv_sec * 1000000 - tv2.tv_usec - tv2.tv_sec * 1000000;
    printf("Read file: %f\nTokenise: %f\n", (double)delta1 / 1000000.0, (double)delta2 / 1000000.0);

    //printf("Output tokens: %f\n", timer.elapsed());
    //printf("Total: %f\n", timer2.elapsed());
    return 0;
}

struct test {
    int a;
    char b;
};

struct test test_create(int a, char b) {
    return (struct test){a, b};
}