#include "signals.h"

#include <signal.h>

volatile sig_atomic_t shutdown_req = 0;

void sigterm_handler(int sig)
{

    const char msg[] = "SIGTERM received\n";
    write(STDERR_FILENO, msg, sizeof(msg) - 1);

    shutdown_req = 1;

    (void)sig;
}

void install_sigterm(void)
{
    struct sigaction sa;
    sa.sa_handler = sigterm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGTERM, &sa, NULL);
}

void restore_signal_handling(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = SIG_DFL; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // restore signals that the parent changed
    sigaction(SIGTERM, &sa, NULL);
}
