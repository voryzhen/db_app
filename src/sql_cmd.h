#ifndef SQL_CMD_H
#define SQL_CMD_H

#include "input_buffer.h"
#include "row.h"

#include "table.h"

typedef enum
{
    PARCE_SUCCESS,
    PARCE_UNDEFINED_CMD,
    PARCE_STRING_TOO_LONG,
    PARCE_NEGATIVE_ID,
    PARCE_SYNTAX_ERROR
} ParceSqlCmdResult;

typedef enum
{
    SQL_CMD_INSERT,
    SQL_CMD_SELECT
} SqlCmdType;

typedef struct
{
    SqlCmdType type;
    Row insert_row;
} SqlCmd;

typedef enum
{
    EXECUTE_CMD_SUCCESS,
    EXECUTE_CMD_TABLE_FULL
} ExecuteCmdResult;

ParceSqlCmdResult parce_sql_cmd (InputBuffer* input_buffer, SqlCmd* cmd);
ParceSqlCmdResult parce_insert  (InputBuffer* input_buffer, SqlCmd* cmd);
void process_sql_cmd (InputBuffer* input_buffer, Table* table);

ExecuteCmdResult execute_sql_cmd (SqlCmd* cmd, Table* table);
ExecuteCmdResult execute_insert  (SqlCmd* cmd, Table* table);
ExecuteCmdResult execute_select  (SqlCmd* cmd, Table* table);

#endif
