#include "process.h"
#include <signal.h>

pid_t process_start(process *p)
{
    pid_t pid = fork();

    if(pid == -1)
    {
        printf("fork failed \n");

        return -1;
    }
    else if(pid == 0) // child code
    {
        execvp(p->argv[1], &p->argv[1]);

        perror("execvp");
        _exit(1);
    }
    else // parent code 
    {
        printf("started program with pid : %d", pid);
    }

    return pid;
}

process_result process_wait(process *p)
{
    int status;
    process_result result;

    if(waitpid(p->pid, &status , 0) == -1)
    {
        perror("waitpid");
    }

    if (WIFEXITED(status)) 
    {
        int exit_status = WEXITSTATUS(status);
        printf("\nChild exited normally with status: %d\n", exit_status);
        p->exit_code = exit_status;
        result.exit_status = exit_status;
    }
    
    else 
    {
        if (WIFSIGNALED(status)) 
        {
            int term_signal = WTERMSIG(status);
            printf("Child was killed by signal: %d\n", term_signal);
            result.term_signal = term_signal;
            result.process_signaled = true;

            /*if (WCOREDUMP(status)) 
            {
                printf("Child produced a core dump.\n");
                p->core_dumped = true;
            }
            else
            {
                p->core_dumped = false;
            }
            */
        }
        else
        {
            result.term_signal = true;
            result.term_signal = -1;
        }
    }

    return result;
}

int process_stop(process *p)
{
    return kill(p->pid, SIGTERM);
}
