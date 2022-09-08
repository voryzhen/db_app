#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include <stdlib.h>

typedef struct
{
    char*   buffer;
    size_t  buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* create_input_buffer ();
void destroy_input_buffer (InputBuffer* input_buffer);

#endif
