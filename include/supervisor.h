#pragma once

#include "types.h"

#include <stdio.h>
#include <unistd.h>

bool should_stop();

void init(char* argv[], process *p);
