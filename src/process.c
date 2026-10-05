#define _GNU_SOURCE

#include "process.h"
#include "signals.h"
#include "supervisor.h"

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
        
        execvp(p->argv[0], &p->argv[0]);

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
        printf("%d exited normally with status: %d\n", p->pid,WEXITSTATUS(status));
        p->exit_code = WEXITSTATUS(status);
    } 
    else if (WIFSIGNALED(status)) 
    {
        printf("%d terminated by signal: %d\n", p->pid,WTERMSIG(status));
        p->term_signal = WTERMSIG(status);

        if (WCOREDUMP(status)) 
        {
            printf("Core dumped.\n");
            p->core_dumped = true;
        }
    } 
    else if (WIFSTOPPED(status)) 
    {
        printf("%d was stopped by signal: %d\n", p->pid,WSTOPSIG(status));
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

void kill_all_children(process *Processes, int p_size)
{
    for(int i = 0; i < p_size; i++)
    {
        process_stop(&Processes[i]);
    }   
}

void process_wait(process* Processes, int p_size)
{
    int status;
    pid_t pid;

    while(1)
    {
        pid = waitpid(-1, &status, 0);

        if(pid > 0) // child 
        {
            printf("got child\n");

            process* p = find_process(Processes ,pid, p_size);

            supervisor_handle_status(status, p);

            handle_restart(p);
        }
        else if(pid == -1)
        {
            if(errno == ECHILD) // no children left
            {
                printf("no children left\n");

                break;
            }

            else if (errno == EINTR)
            {
                printf("waitpid interrupted\n");
                
                // gracefully shutdown all processes 1
                if(should_stop())
                {
                    kill_all_children(Processes, p_size);

                    waitpid(-1, NULL, 0); // reap children so they dont become zombie processes
                }

                break;
            }

            perror("waitpid");

            break;
        }

    }   
}

void process_stop(process *p)
{
    printf("killing pid : %d\n", p->pid);
    
    kill(p->pid, SIGTERM);
}
