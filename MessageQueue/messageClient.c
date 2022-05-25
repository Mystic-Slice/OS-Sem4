#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int client() {
    key_t key;
    int msgQueueId;

    key = ftok("progfile", 65);

    msgQueueId = msgget(key, 0666| IPC_CREAT);
    
    msgrcv(msgQueueId, &message, sizeof(message), 1, 0);

    printf("Data received by the client is: %s\n", message.msg_text);

    msgctl(msgQueueId, IPC_RMID, NULL);

    return 0;
}
