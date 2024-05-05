/*

    The program getsignal sendpid should open the FIFO and write its PID to it before it starts printing numbers.
    The program sendsignal getpid should not read any command-line parameters,
    but instead obtain the PID of getsignal sendpid from the FIFO.
    Both programs should close the FIFO when they no longer need it, but not remove it.

*/

#include <stdio.h>
#include <signal.h>    // kill()
#include <unistd.h>    // sleep()
#include <stdlib.h>    // atoi(), system()
#include <sys/types.h> // mkfifo()
#include <sys/stat.h>  // mkfifo()
#include <fcntl.h>     // open(), O_RDONLY
#include <errno.h>     // errno

void clearTerminal()
{
    system("clear");
}

int main(int argc, char *argv[])
{
    int pid;

    // Create FIFO for communication
    printf("Creating FIFO\n");
    int fifoAction = mkfifo("fifo", 0777);
    if (fifoAction == -1)
    {
        if (errno != EEXIST)
        {
            printf("Error creating FIFO\n");
            return 1;
        }
    }

    // open FIFO
    printf("Opening FIFO\n");
    int fileDescriptor = open("fifo", O_RDONLY);
    if (fileDescriptor == -1)
    {
        printf("Error opening FIFO\n");
        return 1;
    }

    // read PID from FIFO
    printf ("Reading PID from FIFO\n");
    int bytesRead = read(fileDescriptor, &pid, sizeof(pid));
    if (bytesRead == -1)
    {
        printf("Error reading from FIFO\n");
        return 1;
    }

    printf("PID received: %d\n", pid);

    // close FIFO
    printf("Closing FIFO\n");
    int closeAction = close(fileDescriptor);
    if (closeAction == -1)
    {
        printf("Error closing FIFO\n");
        return 1;
    }

    printf("Sending signal 25 to PID: %d\n", pid);

    while (1)
    {
        kill(pid, 25);
        sleep(3);
    }

    return 0;
}