
#include "signals.h"

#include <signal.h>

void sigterm_handler(int sig)
{
    sigterm = 1;

    (void)sig;
}

void install_sigterm(void)
{
    struct sigaction sa;
    sa.sa_handler = sigterm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGCHLD, &sa, NULL);
}
