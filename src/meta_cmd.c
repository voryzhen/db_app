#include "meta_cmd.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

MetaCmdResult execute_meta_cmd (InputBuffer* input_buffer, Table* table)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        close_db(table);
        printf ("Executed.\n");
        exit (EXIT_SUCCESS);
    }
    else
    {
        return META_CMD_UNDEFINED_CMD;
    }
}
