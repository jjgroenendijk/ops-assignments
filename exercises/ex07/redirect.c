/*

    Question: how can you demonstrate that it is really redirect which is writing to
    stdout, and not filter?

*/

#include <stdio.h>  // printf()
#include <stdlib.h> // exit()
#include <unistd.h> // fork(), pipe(), read(), write()

int main(int argc, char *argv[])
{
    // Create pipes
    int stdInPipe[2];  // Parent -> Child
    int stdOutPipe[2]; // Child -> Parent

    // Check if pipes are created successfully
    if (pipe(stdInPipe) == -1)
    {
        perror("pipe");
        exit(1);
    }
    if (pipe(stdOutPipe) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Fork process
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child process PID: %d\n", getpid());

        close(stdInPipe[1]);  // Close write end of inPipe
        close(stdOutPipe[0]); // Close read end of outPipe

        // Redirect stdin and stdout
        dup2(stdInPipe[0], 0);  // Redirect stdin
        dup2(stdOutPipe[1], 1); // Redirect stdout

        // Execute filter
        if (execlp("./filter", "filter", NULL) == -1)
        {
            perror("execlp");
            exit(1);
        }

        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process PID: %d\n", getpid());

        close(stdInPipe[0]);  // Close read end of inPipe
        close(stdOutPipe[1]); // Close write end of outPipe

        // Read from stdin, write to stdout
        char letter;
        read(0, &letter, 1); // read first char from stdin

        // Redirect data
        while (letter != 0x1B)
        {                                    // ESC = Ctrl-[ in shell
            write(stdInPipe[1], &letter, 1); // write char to stdin
            read(stdOutPipe[0], &letter, 1); // read next char from stdout
            write(1, &letter, 1);            // write char to stdout
            read(0, &letter, 1);             // read next char from stdin
        }

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
