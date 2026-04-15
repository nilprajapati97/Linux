/*
🔧 1. Basic Pipe: Parent Writes, Child Reads
==========================================================
Scenario:
Classic unidirectional communication between parent and child using pipe() and fork().

This code demonstrates a simple parent-child process communication using pipes in C.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pipe(fd); // fd[0] - read, fd[1] - write

    pid_t pid = fork();

    if (pid == 0)
    { // Child
        
        close(fd[1]); // Close write end
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);

    }
    else
    { // Parent

        close(fd[0]); // Close read end
        char msg[] = "Hello from parent";
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);

    }

    return 0;
}

/*
Output:
Child received: Hello from parent


This code creates a pipe, forks a child process, and allows the parent to write a message
to the pipe, which the child reads and prints.
This is a basic example of inter-process communication using pipes in C.
This code is designed to be compiled with the C17 standard.
It demonstrates the use of `pipe()`, `fork()`, and basic read/write operations.
It is a foundational example for understanding IPC in C.
This code is suitable for educational purposes and can be extended for more complex IPC scenarios.

*/