#include "sql_cmd.h"

#include <stdio.h>
#include <string.h>

ParceSqlCmdResult parce_sql_cmd (InputBuffer* input_buffer, SqlCmd* cmd)
{
    if (strncmp (input_buffer->buffer, "insert", 6) == 0)
    {
        cmd->type = SQL_CMD_INSERT;

        int cmd_args = sscanf(
            input_buffer->buffer,
            "insert %d %s %s",
            &(cmd->insert_row.id),
            cmd->insert_row.username,
            cmd->insert_row.email
        );

        if (cmd_args < 3)
            return PARCE_SYNTAX_ERROR;

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
