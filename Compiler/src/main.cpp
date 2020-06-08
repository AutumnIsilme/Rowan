#include <cstdio>
#include <fstream>
#include "Lexer.h"

int main(int argc, char **argv) {
    printf("Hello, World!\n");

    std::string file_contents;

    {
    std::ifstream file("test.rw", std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        file_contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&file_contents[0], file_contents.size());
        file.close();
    }
    else
    {
        printf("Could not open source file: %s", "test.rw"); //Temporary hardcoded file.
        system("PAUSE");
        //exit(2);
    }
    }

    auto lexer = Lexer();
    lexer.make_tokens(file_contents);
    printf("%d\n", lexer.tokens->size());
    for (auto token : *lexer.tokens) {
        printf("[%d: %s]\n", token.type, token.contents.c_str());
    }
    return 0;
}
