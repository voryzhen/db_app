#ifndef ROW_CONST_H
#define ROW_CONST_H

#include "row.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

static const uint32_t ID_SIZE       = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE    = size_of_attribute(Row, email);
static const uint32_t ROW_SIZE      = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

static const uint32_t ID_OFFSET       = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET    = USERNAME_OFFSET + USERNAME_SIZE;

#endif
