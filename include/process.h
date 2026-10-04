#pragma once

#include "types.h"

void process_start(process* p);

void process_wait(process* Processes , int p_size);

int process_stop(process *p);

void supervisor_handle_status(int status, process *p);

process* find_process(process* Processes, pid_t pid, int p_size);

void handle_restart(process* p);

