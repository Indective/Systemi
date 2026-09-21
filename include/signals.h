#pragma once

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


volatile sig_atomic_t sigterm = 0;

void sigterm_handler(int sig);

void install_sigterm(void);
