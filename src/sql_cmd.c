#include "sql_cmd.h"

#include "cursor.h"

#include <stdio.h>
#include <string.h>

ParceSqlCmdResult parce_insert (InputBuffer* input_buffer, SqlCmd* cmd)
{
    cmd->type = SQL_CMD_INSERT;

    char* keyword   = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username  = strtok(NULL, " ");
    char* email     = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL)
        return PARCE_SYNTAX_ERROR;

    int id = atoi(id_string);
    if (id < 0)
        return PARCE_NEGATIVE_ID;

    if (strlen(username) > COLUMN_USERNAME_SIZE)
        return PARCE_STRING_TOO_LONG;

    if (strlen(email) > COLUMN_EMAIL_SIZE)
        return PARCE_STRING_TOO_LONG;

    cmd->insert_row.id = id;
    strcpy(cmd->insert_row.username, username);
    strcpy(cmd->insert_row.email, email);

    return PARCE_SUCCESS;
}

ParceSqlCmdResult parce_sql_cmd (InputBuffer* input_buffer, SqlCmd* cmd)
{
    if (strncmp (input_buffer->buffer, "insert", 6) == 0)
    {
        return parce_insert(input_buffer, cmd);
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
    Cursor* cursor = table_end(table);

    serialize_row(row_to_insert, cursor_value(cursor));
    table->num_rows += 1;

    return EXECUTE_CMD_SUCCESS;
}

ExecuteCmdResult execute_select(SqlCmd* cmd, Table* table)
{
    Cursor* cursor = table_start(table);
    Row row;

    while (!(cursor->end_of_table))
    {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }

    free(cursor);
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
        case PARCE_STRING_TOO_LONG:
            printf("String is too long.\n");
            break;
        case PARCE_NEGATIVE_ID:
            printf("ID must be positive.\n");
            break;
    }
}
