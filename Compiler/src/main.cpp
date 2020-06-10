#include <cstdio>
#include <fstream>

#include "Lexer.h"
#include "Timer.h"

int main(int argc, char **argv) {
    printf("Hello, World!\n");

    auto timer2 = Timer();
    auto timer = Timer();

    std::string contents;

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
    }

    printf("Read file: %f\n", timer.elapsed());
    timer.reset();

    auto lexer = Lexer();
    lexer.make_tokens(contents);

    printf("Make tokens: %f\n", timer.elapsed());
    timer.reset();

    printf("%zu\n", lexer.tokens->size());
    for (auto token : *lexer.tokens) {
        printf("[%s: %s]\n", token_type_names[(u16)token.type], token.contents.c_str());
    }

    printf("Output tokens: %f\n", timer.elapsed());
    printf("Total: %f\n", timer2.elapsed());
    return 0;
}
