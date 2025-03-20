#include <stdio.h>
#include <stdlib.h>

typedef struct Buffer {
    char* data;
    size_t len;
    size_t cap;
} Buffer;

// smallBufferSize is an initial allocation minimal capacity.
#define smallBufferSize 64

Buffer* buffer_create() {
    Buffer* buf = (Buffer*)malloc(sizeof(Buffer));
    if(!buf) {
        return NULL;
    }
    buf->len=0;
    buf->cap = smallBufferSize;
    buf->data = (char*)malloc(smallBufferSize);
    if (!buf->data) {
        free(buf);
        return NULL;
    }

    return buf;
}
