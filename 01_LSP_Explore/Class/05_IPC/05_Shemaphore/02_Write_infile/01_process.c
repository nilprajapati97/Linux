/*
Both process writing one line into file.
==============================================================

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
struct sembuf v;

int main()
{
    int id,fd,i;
    char ch[] ="Anil Prajapati";

    // Create a semaphore set with 5 semaphores
    id = semget(5, 5, IPC_CREAT | 0644);
    if (id < 0)
    {
        perror("semget");
        return 1;
    }

    printf("Semaphore set ID = %d\n", id);

    fd = open("file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    // Initialize the semaphore for writing
    v.sem_num = 2; // Semaphore number to use
    v.sem_op = 0;  // Increment the semaphore
    v.sem_flg = 0; // No special flags

    printf("before semop\n");
    if (semop(id, &v, 1) < 0) // Wait
    {
        perror("semop");
    }

    semctl(id, v.sem_num, SETVAL, 1); // Set semaphore value to 1
    printf("after  semop\n");

    for(i=0 ;ch[i] != '\0'; i++)
    {
        if (write(fd, &ch[i], 1) < 0) // Write each character to the file
        {
            perror("write");
            sleep(1);

        }
    }
    printf("Write completed\n");

    semctl(id, 2, SETVAL, 0); // Reset semaphore value to 0


    return 0; // Placeholder for the main function
}