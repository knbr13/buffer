#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

Buffer* buffer_create_with_size(size_t initial_size) {
    Buffer* buf = (Buffer*)malloc(sizeof(Buffer));
    if(!buf) {
        return NULL;
    }

    buf->len = 0;
    if (initial_size == 0) {
        initial_size = smallBufferSize;
    }
    buf->cap = initial_size;
    buf->data = (char*)malloc(initial_size);
    if (!buf->data) {
        free(buf);
        return NULL;
    }

    return buf;
}

void buffer_free(Buffer* buf) {
    if(buf) {
        free(buf->data);
        free(buf);
    }
}

static bool resize_buffer(Buffer* buffer, size_t new_capacity) {
    char* new_data = realloc(buffer->data, new_capacity);
    if (!new_data) return false;

    buffer->data = new_data;
    buffer->cap = new_capacity;
    return true;
}

bool buffer_read_all(Buffer* buffer, FILE* stream) {
    while (true) {
        size_t available = buffer->cap - buffer->len;
        
        if (available == 0) {
            size_t new_cap = buffer->cap ? buffer->cap * 2 : smallBufferSize;
            if (!resize_buffer(buffer, new_cap)) return false;
            available = new_cap - buffer->len;
        }

        size_t bytes_read = fread(buffer->data + buffer->len, 1, available, stream);
        buffer->len += bytes_read;

        if (bytes_read < available) {
            if (feof(stream)) return true;
            if (ferror(stream)) return false;
        }
    }
}

const char* buffer_data(const Buffer* buffer) {
    return buffer->data;
}

size_t buffer_length(const Buffer* buffer) {
    return buffer->len;
}

size_t buffer_capacity(const Buffer* buffer) {
    return buffer->cap;
}

void buffer_clear(Buffer* buffer) {
    buffer->len = 0;
}

bool buffer_trim(Buffer* buffer) {
    if(buffer->cap==buffer->len) return true;
    return resize_buffer(buffer, buffer->len);
}
