#include <pthread.h>
#include <stdio.h>
#include "sharedmemoryserver.c"
#include "sharedmemoryclient.c"

void run(int key) {                                                                                         
    pthread_t thread_id;                                                   
    pthread_create(&thread_id, NULL, server, key);
    pthread_create(&thread_id, NULL, client, key);
    pthread_join(thread_id, NULL);
}

int main() {
    int KEY = 1234;
    run(KEY);
    return 0;
}