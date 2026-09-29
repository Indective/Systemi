#pragma once

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

extern volatile sig_atomic_t shutdown_req;

void sigterm_handler(int sig);

void install_sigterm(void);

void restore_signal_handling(void);
