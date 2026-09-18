#include "process.h"
#include "types.h"
#include "supervisor.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    printf("argc  : %d", argc); // satisfy compiler error

    process p;
    supervisor sup;

    p.argv = argv;
    p.restart = RES_NEVER;

    sup.should_stop = false;

    while(!sup.should_stop)
    {
        process_result result;

        p.pid = process_start(&p);
        //process_stop(&p);
        result = process_wait(&p);

        update(&sup, &p);
    }
    
    return 0;
}

