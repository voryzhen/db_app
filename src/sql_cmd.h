#ifndef SQL_CMD_H
#define SQL_CMD_H

#include "input_buffer.h"

typedef enum
{
    PARCE_SUCCESS,
    PARCE_UNDEFINED_CMD
} ParceSqlCmdResult;

typedef enum
{
    SQL_CMD_INSERT,
    SQL_CMD_SELECT
} SqlCmdType;

typedef struct
{
    SqlCmdType type;
} SqlCmd;

ParceSqlCmdResult parce_sql_cmd (InputBuffer* input_buffer, SqlCmd* cmd);
void execute_sql_cmd (SqlCmd* cmd);
void process_sql_cmd (InputBuffer* input_buffer);

#endif
