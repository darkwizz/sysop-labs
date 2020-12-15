#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void signal_handler(int sigint)
{
    printf("The signal ID is %d\n", sigint);
}


int main()
{
    signal(SIGKILL, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGTERM, signal_handler);
    while (1)
    {
        sleep(2);
    }
    return 0;
}