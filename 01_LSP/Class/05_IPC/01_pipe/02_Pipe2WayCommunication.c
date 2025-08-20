/*
🔄 2. Two-Way Pipe: Bidirectional Communication
==========================================================
This code demonstrates a two-way communication between a parent and child process using pipes in C.
It creates two pipes: one for parent-to-child communication and another for child-to-parent communication.
The parent process writes a message to the child, and the child responds back to the parent.
This is a common pattern in inter-process communication (IPC) where both processes can send and receive
Scenario:

Pipes are unidirectional, so use two pipes for two-way communication.

*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int p2c[2], c2p[2]; // Parent to Child, Child to Parent
    pipe(p2c); pipe(c2p);

    pid_t pid = fork();

    if (pid == 0) { // Child
        close(p2c[1]);
        close(c2p[0]);
        
        char buf[100];
        read(p2c[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        write(c2p[1], "Ack from child", 15);
        
        close(p2c[0]);
        close(c2p[1]);
    
    }
    else
    { // Parent
    
        close(p2c[0]);
        close(c2p[1]);
        // Parent writes to child
        write(p2c[1], "Hello Child", 12);
        char buf[100];

        read(c2p[0], buf, sizeof(buf));
        printf("Parent received: %s\n", buf);
        close(p2c[1]);
        close(c2p[0]);
    }

    return 0;
}
