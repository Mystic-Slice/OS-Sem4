#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int server() {
    key_t key;
    int msgQueueId;

    key = ftok("progfile", 65);

    msgQueueId = msgget(key, 0666| IPC_CREAT);
    
    message.msg_type = 1;

    strcpy(message.msg_text, "Hello World");

    msgsnd(msgQueueId, &message, sizeof(message), 0);

    printf("Data sent by the server is: %s\n", message.msg_text);

    return 0;
}
