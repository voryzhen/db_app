#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

#include "table_const.h"
#include "pager.h"

typedef struct
{
    uint32_t num_rows;
    Pager* pager;
} Table;

void* row_slot(Table* table, uint32_t row_num);
Table* open_db(const char* filename);
void close_db(Table* table);

#endif
