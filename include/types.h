#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

// constants

#define MAX_PROCESSES 50

typedef enum
{
    RES_NEVER,
    RES_ALWAYS,
    RES_ON_FAILURE,
    RES_ON_SUCCESS
    
} restart_policy;

typedef struct
{
    restart_policy policy;
    int count;
    bool pending;
    time_t time;

} restart_handle;

typedef struct
{
    int exit_code;

    bool core_dumped;

    int term_signal;

    int stop_signal;

} status;

typedef struct
{
    char *name;

    char** argv;

    pid_t pid;

    int max_restart;

    status status;

    restart_handle restart;
} process;
