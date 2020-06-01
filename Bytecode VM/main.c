#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TYPE_CHAR 'c'

typedef struct OBJECT_T
{
    uint8_t type;
    union {
        uint8_t u8;
        int8_t i8;
        uint32_t u32;
        int32_t i32;
        float f32;
        void *ptr;
    };
} OBJECT;

typedef struct STACK_t
{
    int top;
    int size;
    OBJECT *stack;
} STACK;

typedef struct DATA_t
{
    int size;
    OBJECT *data;
} DATA;

typedef uint8_t *(*instruction)(uint8_t *, STACK *);

STACK stack_new(int size)
{
    STACK s;
    s.top = 0;
    s.size = size;
    s.stack = (OBJECT *)malloc(sizeof(OBJECT) * size);
    return s;
}

int stack_push(STACK *s, OBJECT o)
{
    s->stack[s->top++] = o;
    return s->top;
}

OBJECT stack_pop(STACK *s)
{
    return s->stack[--(s->top)];
}

OBJECT stack_peek(STACK *s)
{
    return s->stack[s->top - 1];
}

DATA data_new(int size)
{
    DATA d;
    d.size = size;
    d.data = (OBJECT *)malloc(sizeof(OBJECT) * size);
}

void usage()
{
    printf("usage: vm <file>\n");
    exit(1);
}

uint8_t *load_file(char *filename, uint8_t *size)
{
    FILE *f;
    uint8_t *code = NULL;
    struct stat st;
#pragma warning(suppress : 4996)
    if ((f = fopen(filename, "r")))
    {
        fstat(_fileno(f), &st);
        code = (uint8_t *)malloc(st.st_size);
        fread((void *)code, 1, st.st_size, f);
        size = st.st_size;
    }
    else
    {
        printf("Failed to open file.\n");
        usage(); // @TODO
    }
    return code;
}

uint8_t *op_nop(uint8_t *ip, STACK *s)
{
    return ip + 1;
}

uint8_t *op_emit(uint8_t *ip, STACK *s)
{
    OBJECT o = stack_pop(s);
    putchar(o.u8);
    return ip + 1;
}

uint8_t *op_push_char(uint8_t *ip, STACK *s)
{
    OBJECT o;
    o.type = TYPE_CHAR;
    o.u8 = *(ip + 1);
    stack_push(s, o);
    return ip + 2;
}

double get_time()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart / (double)f.QuadPart;
}

struct BIT_TEST_t
{
    union Data {
        struct Inner_data
        {
            char unused : 1;
            char sw2 : 1;
            char sw1 : 1;
            char state : 2;
            char value : 3;
        } inner_data;
        char reg;
    } data;
} BIT_TEST_STRUCT;

int main(int argc, char **argv)
{
    BIT_TEST_STRUCT a = new BIT_TEST_STRUCT;
    double begin = get_time();
    const uint32_t STACK_SIZE = 128;
    uint8_t *code;
    uint8_t *ip;
    uint8_t size = 0;
    STACK data;
    instruction ops[256];
    if (argc != 2)
    {
        usage();
    }
    for (int i = 0; i < 256; i++)
    {
        ops[i] = op_nop;
    }
    ops['c'] = op_push_char;
    ops['e'] = op_emit;
    code = load_file(argv[1], size);
    data = stack_new(STACK_SIZE);
    ip = code;
    double init_end = get_time();
    while (*ip != 'h')
    {
        ip = ops[*ip](ip, &data);
    }
    double end_time = get_time();
    double init_time = init_end - begin;
    double total_time = end_time - begin;
    printf("Exiting program, init time: %f, execution time: %f, total time: %f", init_time, total_time - init_time, total_time);
    return 0;
}
