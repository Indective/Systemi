#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void start_child(char* argv[])
{
    pid_t pid = fork();

    if(pid == -1)
    {
        printf("fork failed \n");

        return;
    }
    else if(pid == 0) // child code
    {
        execvp(argv[1], &argv[1]);

        perror("execvp");
        _exit(1);
    }
    else // parent code 
    {
        printf("started program with pid : %d", pid);

        int status;
        if(waitpid(pid, &status , 0) == -1)
        {
            perror("waitpid");
            return;
        }

        if (WIFEXITED(status)) 
        {
            int exit_status = WEXITSTATUS(status);
            printf("Child exited normally with status: %d\n", exit_status);
        }
        
        else if (WIFSIGNALED(status)) 
        {
            int term_signal = WTERMSIG(status);
            printf("Child was killed by signal: %d\n", term_signal);
            
            #ifdef WCOREDUMP
            if (WCOREDUMP(status)) 
            {
                printf("Child produced a core dump.\n");
            }
            #endif
        }

    }
}

int main(int argc, char* argv[])
{
    start_child(argv);

    return 0;
}