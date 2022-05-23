#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int test_and_set(int* lock) {
    int rv = *lock;
    *lock = 1;
    return rv;
}

void parentFunction(int* lock, int NUM_ITER) {
    
    while(test_and_set(lock));

    sleep(1);
    printf("Parent critical section. Cycles left: %d\n", NUM_ITER);

    *lock = 0;
    sleep(1);
    printf("Parent Out of critical section.\n");
}

void childFunction(int* lock, int NUM_ITER) {
    
    while(test_and_set(lock));

    sleep(1);
    printf("Child critical section. Cycles left: %d\n", NUM_ITER);

    *lock = 0;
    sleep(1);
    printf("Child Out of critical section.\n");
}

int main() {

    int* lockPtr = (int*) malloc(sizeof(int));
    int pid = fork();

    int NUM_ITER = 5;

    if(pid < 0) {
        printf("Child not created\n");
    } else if(pid) {
        // Child
        while(NUM_ITER--) {
            childFunction(lockPtr, NUM_ITER);
        }
    } else {
        // Parent
        while(NUM_ITER--) {
            parentFunction(lockPtr, NUM_ITER);
        }
    }
    return 0;
}
