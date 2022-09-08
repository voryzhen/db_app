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

ExecuteCmdResult execute_insert(SqlCmd* cmd, Table* table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        return EXECUTE_CMD_TABLE_FULL;
    }

    Row* row_to_insert = &(cmd->insert_row);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_CMD_SUCCESS;
}

ExecuteCmdResult execute_select(SqlCmd* cmd, Table* table)
{
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    return EXECUTE_CMD_SUCCESS;
}

ExecuteCmdResult execute_sql_cmd (SqlCmd* cmd, Table* table)
{
    switch (cmd->type)
    {
        case (SQL_CMD_INSERT):
            return execute_insert (cmd, table);
        case (SQL_CMD_SELECT):
            return execute_select (cmd, table);
    }
}

void process_sql_cmd (InputBuffer* input_buffer, Table* table)
{
    SqlCmd cmd;
    switch ( parce_sql_cmd (input_buffer, &cmd) ) {
        case PARCE_SUCCESS:
            switch (execute_sql_cmd (&cmd, table))
            {
                case EXECUTE_CMD_SUCCESS:
                    printf ("Executed.\n");
                    break;
                case EXECUTE_CMD_TABLE_FULL:
                    printf ("Insert error. Memory is full.\n");
                    break;
            }
            break;
        case PARCE_SYNTAX_ERROR:
            printf ("Syntax error in sql command '%s'.\n", input_buffer->buffer);
            break;
        case PARCE_UNDEFINED_CMD:
            printf ("Undefined sql command '%s'.\n", input_buffer->buffer);
            break;
    }
}
