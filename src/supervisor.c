#include "signals.h"
#include "types.h"
#include "supervisor.h"
#include "process.h"

#include <errno.h>

bool should_stop()
{
    // terminate or not
    if (shutdown_req) 
    {
        shutdown_req = 0;
        return true;
    }
    return false;
}

void init(char *argv[], process *p)
{
    printf("%d \n", getpid());

    install_sigterm();

    int p_count = (sizeof(argv) / sizeof(argv[0])) - 1;
    for(int i = 0; i < p_count; i++)
    {
        p[i].argv = argv[i+1];
        p[i].restart = RES_NEVER;
    }

}

