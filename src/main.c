#include "process.h"
#include "types.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    printf("argc  : %d", argc); // satisfy compiler error

    process p;
    p.argv = argv;
    p.restart = RES_ALWAYS;

    while(1)
    {
        process_result result;

        p.pid = process_start(&p);
        //process_stop(&p);
        result = process_wait(&p);
    }
    
    return 0;
}

