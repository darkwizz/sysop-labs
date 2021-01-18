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

    if (strstr(argv[1], "#") != NULL || strstr(argv[1], "<") != NULL ||
    strstr(argv[1], ">") != NULL)
    {
        printf("#, <, > cannot be in a username\n");
        return -7;
    }
    
    strcpy(USERNAME, argv[1]);
    printf("Hello, %s\n", USERNAME);

    chat_sem = sem_open("/CHAT_SEMAPHORE", O_CREAT, S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP, 1);
    if (chat_sem == SEM_FAILED)
    {
        printf("Cannot open semaphore, error %s\n", strerror(errno));
        return -5;
    }
    // printf("Open semaphore successfully\n");
    read_sent_messages();

    char message[240];
    while (1)
    {
        printf("You (or type EXIT): ");
        scanf("%[^\n]%*c", message);
        if (strcmp("EXIT", message) == 0)
        {
            break;
        }
        send_message(USERNAME, message);
    }

    sem_close(chat_sem);
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
    char sep[] = "#";
    while ((read = getline(&line, &len, messages)) != -1)
    {
        char* tempstr = calloc(strlen(line) + 1, sizeof(char));
        strcpy(tempstr, line);
        char* msg_username = strtok(tempstr, sep);
        char* msg_rest = strtok(NULL, sep);
        if (strcmp(msg_username, USERNAME) == 0)
        {
            char* changed_line = calloc(strlen(msg_rest) + strlen("<You>#") + 1, sizeof(char));
            sprintf(changed_line, "%s#%s", "<You>", msg_rest);
            printf("%s", changed_line);
            free(changed_line);
            continue;
        }
        printf("%s", line);
        free(tempstr);
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