#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

int client(int key) {
	printf("Here");
    int shmid = shmget((key_t)key, 1024, IPC_CREAT | 0666);

    if(shmid < 0) {
        perror("Shared memory not created.\n");
        exit(1);
    }

    void *shm = shmat(shmid, NULL, 0);

    if(shm == (char *)-1) {
        perror("Memory not attached");
        exit(1);
    }

    printf("Message read by client: %s\n", (char*) shm);
}