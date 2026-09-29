#include "signals.h"
#include "types.h"
#include "supervisor.h"
#include "process.h"

#include <errno.h>

void update(supervisor *sup, process *p, process_result *res)
{
    // decide wether to restart
    if(p->restart == RES_ALWAYS)
    {
        sup->should_stop = false;
    }
    else if(p->restart == RES_NEVER)
    {
        sup->should_stop = true;
    }
    else if(p->restart == RES_ON_FAILURE)
    {
        if(p->exit_code != 0)
        {
            sup->should_stop = false;
        }
    }
    else if(p->restart == RES_ON_SUCCESS)
    {
        if(p->exit_code == 0)
        {
            sup->should_stop = false;
        }
    }

    // terminate or not
    if (shutdown_req) 
    {
        shutdown_req = 0;

        printf("terminating\n");

        //process_stop(p);
        //process_wait(p);

        sup->should_stop = true;
    }

}

void init(void)
{
    printf("%d \n", getpid());

    install_sigterm();
}

