#include "cmd.h"

#include <stdio.h>
#include <stdbool.h>

#include "meta_cmd.h"
#include "sql_cmd.h"

void print_prompt () { printf("db > "); }

void read_input (InputBuffer* input_buffer)
{
    ssize_t bytes_read = getline (&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf ("Error reading input\n");
        destroy_input_buffer (input_buffer);
        exit (EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1; // new line symbol
    input_buffer->buffer[bytes_read - 1] = 0;
}

void process_cmd (InputBuffer* input_buffer)
{
    if ( input_buffer->buffer[0] == '.' )
    {
        if ( execute_meta_cmd (input_buffer) == META_CMD_UNDEFINED_CMD )
            printf("Undefined meta command '%s'\n", input_buffer->buffer);
    }
    else
    {
        process_sql_cmd (input_buffer);
    }
}

void run_db_app()
{
    InputBuffer* input_buffer = create_input_buffer ();
    while (true)
    {
        print_prompt ();
        read_input   (input_buffer);
        process_cmd  (input_buffer);
    }
}
