#define _GNU_SOURCE

#include "process.h"
#include "signals.h"

#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

void process_start(process* p)
{
    fflush(stdout);

    pid_t pid = fork();

    if(pid == -1)
    {
        printf("fork failed \n");
    }
    else if(pid == 0) // child code
    {
        restore_signal_handling();
        
        execvp(p->argv[1], &p->argv[1]);

        perror("execvp");
        _exit(1);
    }
    else // parent code 
    {
        printf("started program with pid : %d\n", pid);
        p->pid = pid;
    }


}

void supervisor_handle_status(int status, process *p)
{
    if (WIFEXITED(status)) 
    {
        printf("Child exited normally with status: %d\n", WEXITSTATUS(status));
        p->exit_code = WEXITSTATUS(status);
    } 
    else if (WIFSIGNALED(status)) {

        printf("Child terminated by signal: %d\n", WTERMSIG(status));
        p->term_signal = WTERMSIG(status);

        if (WCOREDUMP(status)) 
        {
            printf("Core dumped.\n");
            p->core_dumped = true;
        }
    } 
    else if (WIFSTOPPED(status)) 
    {
        printf("Child was stopped by signal: %d\n", WSTOPSIG(status));
        p->stop_signal = WSTOPSIG(status);
    } 
    else if (WIFCONTINUED(status)) 
    {
        printf("Child was continued.\n");
    }
}

process* find_process(process *Processes, pid_t pid, int p_size)
{
    for(int i = 0; i < p_size; i++)
    {
        if(Processes[i].pid == pid)
        {
            return &Processes[i];
        }
    }

    return NULL;
}

void handle_restart(process *p)
{
    if(p->restart == RES_ALWAYS)
    {
        process_start(p);
    }
    else if(p->restart == RES_ON_SUCCESS)
    {
        if(p->exit_code == 0)
        {
            process_start(p);
        }
    }
    else if(p->restart == RES_ON_FAILURE)
    {
        if(p->exit_code != 0)
        {
            process_start(p);
        }
    }
}

void process_wait(process* Processes, int p_size)
{
    int status;
    pid_t pid;

    while(1)
    {
        pid = waitpid(-1, &status, 0);

        if(errno == ECHILD) // no children left
        {
            break;
        }

        process* p = find_process(Processes ,pid, p_size);
    
        if (errno == EINTR)
        {
            printf("got sigterm !\n");

            process_stop(p);
        }
        else 
        {
            perror("waitpid");
        }

        supervisor_handle_status(status, p);

        handle_restart(p);
    }   
}

int process_stop(process *p)
{
    printf("killing process\n");
    return kill(p->pid, SIGTERM);
}
