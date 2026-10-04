#include "signals.h"
#include "process.h"
#include "types.h"
#include "supervisor.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    process Processes[MAX_PROCESSES];

    int p_size = sup_init(argv, Processes);

    printf("argc  : %d\n", argc); // satisfy compiler error

    for(int i = 0; i < p_size; i++)
    {
        process_start(&Processes[i]);
    }

    process_wait(Processes, p_size);

    return 0;
}

