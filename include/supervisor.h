#pragma once

#include "types.h"

#include <stdio.h>
#include <unistd.h>

bool should_stop(void);

int sup_init(char* argv[], process *p);
