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
    int count = (sizeof(Processes) / sizeof(Processes[0]));

    init(argv, Processes);

    printf("argc  : %d\n", argc); // satisfy compiler error

    for(int i = 0; i < count; i++)
    {
        process_start(&Processes[i]);
    }

    process_wait(Processes);

    return 0;
}

