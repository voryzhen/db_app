#ifndef META_CMD_H
#define META_CMD_H

#include "input_buffer.h"

typedef enum
{
    META_CMD_SUCCESS,
    META_CMD_UNDEFINED_CMD
} MetaCmdResult;

MetaCmdResult execute_meta_cmd (InputBuffer* input_buffer);

#endif
