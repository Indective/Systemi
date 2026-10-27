#pragma once

#include "types.h"

#include <stdio.h>
#include <unistd.h>
#include <cJSON.h>

bool should_stop(void);

bool create_processes(const cJSON *json_data, process *p, size_t *count);

int sup_init(char *argv[], process *p);

void exit_cleanup(process *p, int p_size);

