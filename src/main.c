#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char*   buffer;
  size_t  buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* create_input_buffer ()
{
    InputBuffer* input_buffer = (InputBuffer*) malloc (sizeof(InputBuffer));

    input_buffer->buffer        = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length  = 0;

    return input_buffer;
}

void print_prompt () { printf("db > "); }

void read_input (InputBuffer* input_buffer)
{
    ssize_t bytes_read = getline (&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1; // new line symbol
    input_buffer->buffer[bytes_read - 1] = 0;
}

void destroy_input_buffer (InputBuffer* input_buffer)
{
    free (input_buffer->buffer);
    free (input_buffer);
}




typedef enum {
    META_CMD_SUCCESS,
    META_CMD_UNDEFINED_CMD
} MetaCmdResult;

typedef enum { PARCE_SUCCESS, PARCE_UNDEFINED_CMD } ParceSqlCmdResult;

MetaCmdResult execute_meta_cmd (InputBuffer* input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_CMD_UNDEFINED_CMD;
    }
}

typedef enum
{
    SQL_CMD_INSERT,
    SQL_CMD_SELECT
} SqlCmdType;

typedef struct
{
  SqlCmdType type;
} SqlCmd;

ParceSqlCmdResult parce_sql_cmd (InputBuffer* input_buffer, SqlCmd* cmd)
{
    if (strncmp (input_buffer->buffer, "insert", 6) == 0)
    {
        cmd->type = SQL_CMD_INSERT;
        return PARCE_SUCCESS;
    }
    if (strcmp (input_buffer->buffer, "select") == 0)
    {
        cmd->type = SQL_CMD_SELECT;
        return PARCE_SUCCESS;
    }

    return PARCE_UNDEFINED_CMD;
}

void execute_sql_cmd (SqlCmd* cmd)
{
    switch (cmd->type)
    {
        case (SQL_CMD_INSERT):
            printf("Executing insert.\n");
            break;
        case (SQL_CMD_SELECT):
            printf("Executing select.\n");
            break;
    }
}

void process_sql_cmd (InputBuffer* input_buffer)
{
    SqlCmd cmd;
    switch ( parce_sql_cmd (input_buffer, &cmd) ) {
        case PARCE_SUCCESS:
            execute_sql_cmd (&cmd);
            printf ("Executed.\n");
            break;
        case PARCE_UNDEFINED_CMD:
            printf ("Undefined sql command '%s'.\n", input_buffer->buffer);
            break;
    }
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

int main (int argc, char* argv[])
{
    InputBuffer* input_buffer = create_input_buffer ();

    while (true)
    {
        print_prompt ();
        read_input   (input_buffer);
        process_cmd  (input_buffer);
    }

    destroy_input_buffer (input_buffer);
}
