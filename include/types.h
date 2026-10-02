#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// constants

#define MAX_PROCESSES 50

// typedef / struct

typedef enum
{
    RES_NEVER,
    RES_ALWAYS,
    RES_ON_FAILURE,
    RES_ON_SUCCESS
    
} restart_policy;

typedef struct
{
    char** argv;
    pid_t pid;

    int exit_code;

    bool core_dumped;

    int term_signal;

    int stop_signal;

    restart_policy restart;

} process;
