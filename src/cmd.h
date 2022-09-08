#ifndef CMD_H
#define CMD_H

#include "input_buffer.h"

void print_prompt ();
void read_input (InputBuffer* input_buffer);
void process_cmd (InputBuffer* input_buffer);
void run_db_app();

#endif
