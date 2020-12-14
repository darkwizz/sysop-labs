#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();
    int num_to_read;
    pid_t proc_pid;
    FILE* f = fopen("../.gitignore", "r");
    int* dynamic_int = (int*) malloc(sizeof(int));

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    {
        proc_pid = getpid();
        printf("Child Process PID: %d\n", proc_pid);
        // execlp("/bin/ls", "ls", NULL);
        printf("Enter number in Child Proc: ");
        scanf("%d", &num_to_read);
    }
    else
    {
        proc_pid = getpid();
        printf("Parent PID (from getpid() call): %d\n", proc_pid);
        printf("Parent PID (from fork() call): %d\n", pid);

        printf("Enter number in Parent Proc: ");
        scanf("%d", &num_to_read);
        //wait(NULL);
        printf("\nChild Complete\n");
    }
    
    if (f != NULL)
    {
        printf("\nClosing file for PID: %d\n", proc_pid);
        fclose(f);
    }
    if (dynamic_int != NULL)
    {
        printf("\nReleasing allocated memory for PID: %d\n", proc_pid);
        free(dynamic_int);
    }
    printf("Entered number in PID %d: %d\n", proc_pid, num_to_read);
    return 0;
}