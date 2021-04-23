#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Frontend/Scanner.h>
#include <Timer.h>

void print_help(const char *exec) {
    printf("Usage: %s [filename]\n", exec);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    Timer timer2 = timer_create();
    //Timer timer = timer_create();

    /*FILE* file = fopen("test2.rw", "rb");
    if (file == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }*/

    /*struct timeval tv2;
    gettimeofday(&tv2, NULL);

    printf("Read file: %f\n", timer_elapsed(&timer));*/
    //timer_reset(&timer);

    //printf("Init: %f\n", timer_elapsed(&timer));
    //timer_reset(&timer);

    uint64 token_count;
    /*Token *tokens = */scan(argv[1], &token_count);

    printf("Token count: %llu\n", token_count);
    //printf("Output tokens: %f\n", timer_elapsed(&timer));
    printf("Time: %f\n", timer_elapsed(&timer2));
    return 0;
}
