#include <stdio.h>  // printf()
#include <stdlib.h> // exit()
#include <unistd.h> // fork(), pipe(), read(), write()

int main(int argc, char *argv[])
{
    // Create pipes
    int inPipe[2];
    int outPipe[2];

    if (pipe(inPipe) == -1)
    {
        perror("pipe");
        exit(1);
    }

    if (pipe(outPipe) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child process PID: %d\n", getpid());

        close(inPipe[1]);   // Close read end of inPipe
        close(outPipe[0]);  // Close write end of outPipe

        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process PID: %d\n", getpid());

        close(inPipe[0]);   // Close read end of inPipe
        close(outPipe[1]);  // Close write end of outPipe

        exit(0);
    }
    else
    {
        // Error
        perror("fork");
        exit(1);
    }

    return 0;
}
