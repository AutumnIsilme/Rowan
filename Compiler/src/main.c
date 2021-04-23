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
<<<<<<< HEAD
    //Timer timer = timer_create();
=======
    Timer timer = timer_create();

    FILE* file = fopen("test2.rw", "rb");
    if (file == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);
>>>>>>> 8d45f37492ab6ec1484f45df33e93d574214eef7

    /*FILE* file = fopen("test2.rw", "rb");
    if (file == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }*/

<<<<<<< HEAD
    /*struct timeval tv2;
    gettimeofday(&tv2, NULL);

    printf("Read file: %f\n", timer_elapsed(&timer));*/
    //timer_reset(&timer);
=======
    printf("Bytes read: %#lx\n", bytes_read);

    fclose(file);

    printf("Read file: %f\n", timer_elapsed(&timer));
    timer_reset(&timer);

    Scanner *scanner = scanner_init(file_contents, file_size);
>>>>>>> 8d45f37492ab6ec1484f45df33e93d574214eef7

    //printf("Init: %f\n", timer_elapsed(&timer));
    //timer_reset(&timer);

    uint64 token_count;
    /*Token *tokens = */scan(argv[1], &token_count);

    printf("Token count: %llu\n", token_count);
    //printf("Output tokens: %f\n", timer_elapsed(&timer));
    printf("Time: %f\n", timer_elapsed(&timer2));
    return 0;
}
