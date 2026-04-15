#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t lock;

const char *filename = "shared.txt";

void* writer_thread(void *arg) {
    FILE *fp;

    pthread_mutex_lock(&lock); // Lock before writing

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Writer: fopen");
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    fprintf(fp, "Hello from writer thread!\n");
    fclose(fp);

    printf("Writer: Data written to file.\n");

    pthread_mutex_unlock(&lock); // Unlock after writing

    return NULL;
}

void* reader_thread(void *arg) {
    sleep(1);  // Give time for writer to write before reading

    pthread_mutex_lock(&lock); // Lock before reading

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Reader: fopen");
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    char buffer[256];
    printf("Reader: Reading from file:\n");
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("Reader: %s", buffer);
    }
    fclose(fp);

    pthread_mutex_unlock(&lock); // Unlock after reading

    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    // Create writer and reader threads
    pthread_create(&tid1, NULL, writer_thread, NULL);
    pthread_create(&tid2, NULL, reader_thread, NULL);

    // Wait for both threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
