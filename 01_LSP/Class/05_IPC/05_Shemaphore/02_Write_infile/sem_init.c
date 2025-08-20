/*
🧾 Step 1: sem_init.c – Initialize Semaphore (Run Once)
===========================================================
*/

// sem_init.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok("file.txt", 65);
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid < 0) {
        perror("semget");
        return 1;
    }

    // Initialize semaphore 0 to 1 (unlocked state)
    if (semctl(semid, 0, SETVAL, 1) < 0) {
        perror("semctl");
        return 1;
    }

    printf("Semaphore initialized with ID: %d\n", semid);
    return 0;
}
