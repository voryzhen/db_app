#include "meta_cmd.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

MetaCmdResult execute_meta_cmd (InputBuffer* input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        destroy_input_buffer (input_buffer);
        printf ("Executed.\n");
        exit (EXIT_SUCCESS);
    }
    else
    {
        return META_CMD_UNDEFINED_CMD;
    }
}
