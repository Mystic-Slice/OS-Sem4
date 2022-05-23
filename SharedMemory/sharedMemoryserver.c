#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int server(int key) {

    int shmid = shmget((key_t)key, 1024, IPC_CREAT | 0666);

    if(shmid < 0) {
        perror("Shared memory not created.\n");
        exit(1);
    }

    char *shm = shmat(shmid, NULL, 0);

    if(shm == (char *)-1) {
        perror("Memory not attached");
        exit(1);
    }

    strcpy(shm, "Hi! This is a message from the server!");
    printf("Message written by server: %s\n", shm);
    exit(0);
}