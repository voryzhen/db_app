#include "input_buffer.h"

InputBuffer* create_input_buffer ()
{
    InputBuffer* input_buffer = (InputBuffer*) malloc (sizeof(InputBuffer));

    input_buffer->buffer        = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length  = 0;

    return input_buffer;
}

void destroy_input_buffer (InputBuffer* input_buffer)
{
    free (input_buffer->buffer);
    free (input_buffer);
}
