#include "signals.h"
#include "types.h"
#include "supervisor.h"
#include "process.h"

#include <errno.h>

bool should_stop(void)
{
    // terminate or not
    if (shutdown_req) 
    {
        shutdown_req = 0;
        return true;
    }
    return false;
}

int sup_init(char* argv[], process *p)
{
    int p_size = 0;

    printf("%d \n", getpid());

    install_sigterm();

    while (argv[p_size] != NULL) 
    {
        p_size++;
    }

    p_size --; // minus one for the arg[0] (calling the program)

    for(int i = 0; i < p_size; i++)
    {
        p[i].argv = &argv[i+1]; // temporary for children with no arguments (only calling the child )
        p[i].restart = RES_NEVER;
    }

    return p_size;

}

