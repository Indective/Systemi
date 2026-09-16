#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct
{
    char** argv;
    pid_t pid;

    int exit_code;
    bool core_dumped;
    int term_signal;

} process;

pid_t process_start(process *p);
void process_wait(process *p);
int process_stop(process *p);
