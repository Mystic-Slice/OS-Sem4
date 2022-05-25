#include <pthread.h>
#include "messageServer.c"
#include "messageClient.c"

int main() {
    pthread_t thread_id_server, thread_id_client;

    pthread_create(&thread_id_server, NULL, server, NULL);
    pthread_create(&thread_id_client, NULL, client, NULL);

    pthread_join(thread_id_server, NULL);
    pthread_join(thread_id_client, NULL);

    return 0;
}
