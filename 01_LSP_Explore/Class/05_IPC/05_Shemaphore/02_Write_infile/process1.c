/*
🧾 Step 2: process1.c – First Process Writing to File
=====================================================
*/

// process1.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

struct sembuf lock = {0, -1, 0};  // P operation
struct sembuf unlock = {0, 1, 0}; // V operation

int main() {
    key_t key = ftok("file.txt", 65);
    int semid = semget(key, 1, 0666);
    if (semid < 0) {
        perror("semget");
        return 1;
    }

    int fd = open("file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    semop(semid, &lock, 1);  // Lock
    write(fd, "Process1: Anil Prajapati\n", 25);
    semop(semid, &unlock, 1); // Unlock

    close(fd);
    return 0;
}
