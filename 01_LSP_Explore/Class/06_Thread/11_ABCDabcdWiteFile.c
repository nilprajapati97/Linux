#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
FILE *fp;

void* write_caps(void *arg) {
    pthread_mutex_lock(&lock);
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        fputc(ch, fp);
        fflush(fp);
        usleep(10000); // simulate some delay
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* write_smalls(void *arg) {
    pthread_mutex_lock(&lock);
    for (char ch = 'a'; ch <= 'z'; ch++) {
        fputc(ch, fp);
        fflush(fp);
        usleep(10000); // simulate some delay
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Open file
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("File open failed");
        return 1;
    }

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    // Create threads
    pthread_create(&t1, NULL, write_caps, NULL);
    pthread_create(&t2, NULL, write_smalls, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Cleanup
    fclose(fp);
    pthread_mutex_destroy(&lock);

    printf("Letters written to output.txt\n");
    return 0;
}
