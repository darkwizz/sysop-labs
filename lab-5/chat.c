#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>


#define USERNAME_LEN 10
char USERNAME[USERNAME_LEN];
// sem_t* chat_sem = sem_open("CHAT_SEM", O_CREAT)
const char* MSG_FILE_PATH = "chat.msg";


int main(int argc, char** argv)
{
    printf("%s\n", argv[0]);
    if (argc < 2)
    {
        printf("Username was not passed\n");
        return -1;
    }

    if (strlen(argv[1]) > USERNAME_LEN)
    {
        printf("Too long username\n");
        return -2;
    }
    
    strcpy(USERNAME, argv[1]);
    printf("Hello, %s\n", USERNAME);

    while (1)
    {
    }

    return 0;
}