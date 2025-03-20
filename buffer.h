#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>

typedef struct Buffer Buffer;

Buffer* buffer_create();
Buffer* buffer_create_with_size(size_t initial_size);

#endif