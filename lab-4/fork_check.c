#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    {
        pid_t proc_pid = getpid();
        printf("Child Process PID: %d\n", proc_pid);
        execlp("/bin/ls", "ls", NULL);
    }
    else
    {
        pid_t proc_pid = getpid();
        printf("Parent PID (from getpid() call): %d\n", proc_pid);
        printf("Parent PID (from fork() call): %d\n", pid);
        wait(NULL);
        printf("Child Complete");
    }
    
    return 0;
}