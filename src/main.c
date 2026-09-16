#include "process.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    process p;
    p.argv = argv;

    process_start(&p);
    process_wait(&p);

    return 0;
}