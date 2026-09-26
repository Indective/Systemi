#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main()
{
    sleep(3);

    kill(getpid(), SIGTERM);

    return 0;
}
