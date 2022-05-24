#include <pthread.h>
#include <stdio.h>
#include "sharedmemoryserver.c"
#include "sharedmemoryclient.c"

void run(int key) {                                                                                         
    pthread_t thread_id_server, thread_id_client;                                                   
    pthread_create(&thread_id_server, NULL, server, key);
    pthread_create(&thread_id_client, NULL, client, key);
	pthread_join(thread_id_server, NULL);
    pthread_join(thread_id_client, NULL);
}

int main() {
    int KEY = 1234;
    run(KEY);
    return 0;
}