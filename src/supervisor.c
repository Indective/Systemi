#include "types.h"
#include "supervisor.h"

void update(supervisor *sup, process *p)
{

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
    
}
