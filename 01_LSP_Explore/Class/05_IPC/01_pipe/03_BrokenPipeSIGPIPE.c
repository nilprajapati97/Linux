/*
3. Broken Pipe: SIGPIPE Scenario
==========================================================
Scenario:
            Writing to a pipe with no reader triggers SIGPIPE.

*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGPIPE!\n");
}

int main() {
    signal(SIGPIPE, handler);

    int fd[2];
    pipe(fd);
    close(fd[0]); // Close read end

    printf("Writing to pipe with no reader...\n");
    // Attempt to write to the pipe without a reader
    // This will trigger SIGPIPE since the read end is closed
    // Note: This will terminate the process unless handled
    // In a real application, you would check if the pipe is writable before writing
    // Here we intentionally write to trigger the SIGPIPE
    // This is for demonstration purposes only
    // In practice, you should avoid writing to a closed pipe
    // and handle the situation gracefully.

    write(fd[1], "Test", 4); // Triggers SIGPIPE
    close(fd[1]);

    return 0;
}
