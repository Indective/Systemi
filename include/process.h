#pragma once

#include "types.h"

pid_t process_start(process *p);
process_result process_wait(process *p);
int process_stop(process *p);
process_result supervisor_handle_status(int status, process *p);
