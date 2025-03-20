#include <stdio.h>

typedef struct Buffer {
    char* data;
    size_t len;
    size_t cap;
} Buffer;
