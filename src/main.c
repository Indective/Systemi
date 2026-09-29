#include "signals.h"
#include "process.h"
#include "types.h"
#include "supervisor.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    // init
    init();

    printf("argc  : %d\n", argc); // satisfy compiler error

    process p;
    supervisor sup;
    process_result res;

    p.argv = argv;
    p.restart = RES_ALWAYS;

    sup.should_stop = false;

    while(!sup.should_stop)
    {
        p.pid = process_start(&p);
        res = process_wait(&p);
        
        //process_stop(&p);

        update(&sup, &p, &res);
    }
    
    return 0;
}

