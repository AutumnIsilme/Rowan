#include <cstdio>
#include <fstream>
#include <string.h>

#include "Lexer.h"
#include "Timer.h"

int main(int argc, char **argv) {
    printf("Hello, World!\n");

    auto timer2 = Timer();
    auto timer = Timer();

    FILE* file = fopen("test_4M_lines.rw", "rb");

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* file_contents = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(file_contents, sizeof(char), fileSize, file);
    file_contents[bytesRead] = '\0';

    fclose(file);

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

    printf("Read file: %f\n", timer.elapsed());
    timer.reset();

    auto lexer = Lexer::init(file_contents);

    printf("Init: %f\n", timer.elapsed());
    timer.reset();

    //printf("%zu\n", Lexer_Old.tokens->size());
    Token t = Token(TT_CONTINUE, 0, 0, 0, 0);
    while (t.type != TT_EOF) {
        //printf("Making token!");
        t = lexer->scanToken();
        //printf("Copying to contents!");
        //char* contents = (char*)malloc(t.length+1);
        //memcpy(contents, t.token, t.length);
        //contents[t.length] = '\0';
        //printf("End!");
        //printf("[%s: %s]\n", token_type_names[(u16)t.type], contents);
    }

    printf("Output tokens: %f\n", timer.elapsed());
    printf("Total: %f\n", timer2.elapsed());
    return 0;
}
