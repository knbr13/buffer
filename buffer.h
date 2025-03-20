#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Buffer Buffer;

Buffer* buffer_create();

Buffer* buffer_create_with_size(size_t initial_size);

void buffer_free(Buffer* buf);

bool buffer_read_all(Buffer* buffer, FILE* stream);

const char* buffer_data(const Buffer* buffer);

size_t buffer_length(const Buffer* buffer);

void buffer_clear(Buffer* buffer);

bool buffer_trim(Buffer* buffer);

#endif