/*
🧹 Optional: sem_cleanup.c – Remove Semaphore Set
======================================================
*/

// sem_cleanup.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok("file.txt", 65);
    int semid = semget(key, 1, 0666);

    if (semctl(semid, 0, IPC_RMID) < 0) {
        perror("semctl IPC_RMID");
        return 1;
    }

    printf("Semaphore removed\n");
    return 0;
}
