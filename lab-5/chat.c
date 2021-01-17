#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>  // for O_* constants
#include <sys/stat.h>  // for mode constants
#include <semaphore.h>
#include <errno.h>


#define USERNAME_LEN 10
char USERNAME[USERNAME_LEN];
const char* MSG_FILE_PATH = "chat.msg";

sem_t* chat_sem;

void send_message(char* username, char* message);
void read_sent_messages();


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

    chat_sem = sem_open("/CHAT_SEM_NEW", O_CREAT, S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP, 1);
    if (chat_sem == SEM_FAILED)
    {
        printf("Cannot open semaphore, error %s\n", strerror(errno));
        return -5;
    }
    printf("Open semaphore successfully\n");
    read_sent_messages();

    char message[240];
    while (1)
    {
        printf("You: ");
        scanf("%[^\n]%*c", message);
        send_message(USERNAME, message);
    }

    return 0;
}

void read_sent_messages()
{
    sem_wait(chat_sem);
    FILE* messages = fopen(MSG_FILE_PATH, "r");
    if (!messages)
    {
        printf("No messages for now\n");
        sem_post(chat_sem);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, messages)) != -1)
    {
        printf("%s", line);
    }
    fclose(messages);
    sem_post(chat_sem);
}

void send_message(char* username, char* message)
{
    sem_wait(chat_sem);
    FILE* messages = fopen(MSG_FILE_PATH, "a");
    if (!messages)
    {
        printf("Could not open file to send messages\n");
        sem_post(chat_sem);
        exit(errno);
    }

    char full_msg[255];
    sprintf(full_msg, "%s# %s\n", username, message);
    fwrite(full_msg, sizeof(char), strlen(full_msg), messages);
    fclose(messages);
    sem_post(chat_sem);
}