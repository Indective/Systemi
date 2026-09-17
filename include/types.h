#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct
{
    bool should_stop;

} supervisor;  

typedef enum
{
    RES_NEVER,
    RES_ALWAYS,
    RES_ON_FAILURE,
    RES_ON_SUCCESS
    
} restart_policy;

typedef struct
{
    int exit_status;
    bool process_signaled;
    int term_signal;

} process_result;


typedef struct
{
    char** argv;
    pid_t pid;

    int exit_code;
    bool core_dumped;
    int term_signal;
    restart_policy restart;

} process;
