/*

    The program getsignal sendpid should open the FIFO and write its PID to it before it starts printing numbers.
    The program sendsignal getpid should not read any command-line parameters,
    but instead obtain the PID of getsignal sendpid from the FIFO.
    Both programs should close the FIFO when they no longer need it, but not remove it.

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>    // write(), sleep()
#include <stdlib.h>    // system()
#include <stdbool.h>   // bool
#include <sys/types.h> // mkfifo()
#include <sys/stat.h>  // mkfifo()
#include <fcntl.h>     // open(), O_RDONLY
#include <errno.h>     // errno
#include <string.h>    // strlen()

bool verbose = false; // Set to true to enable more detailed output information

volatile char number = '0';

void signalHandler(int signal)
{
    if (verbose)
    {
        printf("Signal received: %d\n", signal);
    }

    if (signal == 25)
    {
        if (number == '9')
        {
            number = '0';
        }
        else
        {
            number = number + 1;
        }
    }
}

void clearTerminal()
{
    system("clear");
}

void returnKey()
{
    write(STDOUT_FILENO, "\r", 1);
}

int main()
{
    // Declare needed variables
    int pid = getpid();
    printf ("PID: %d\n", pid);

    // Set up signal handler
    struct sigaction action;
    action.sa_handler = signalHandler;
    sigaction(25, &action, NULL);

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

    // Open FIFO for writing
    printf("Opening FIFO\n");
    int fileDescriptor = open("fifo", O_WRONLY);
    if (fileDescriptor == -1)
    {
        printf("Error opening FIFO\n");
        return 1;
    }

    // Write PID to FIFO
    printf("Writing PID: %d (%d) to FIFO\n", pid, sizeof(pid));

    if (write(fileDescriptor, &pid, sizeof(pid)) == -1)
    {
        printf("Error writing to FIFO\n");
        return 1;
    }

    // Close FIFO
    printf("Closing FIFO\n");
    int closeAction = close(fileDescriptor);
    if (closeAction == -1)
    {
        printf("Error closing FIFO\n");
        return 1;
    }

    // Clear the terminal window
    //clearTerminal();

    printf("Process ID: %d\n", getpid());

    while (1)
    {
        // Write number to stdout unbuffered
        write(STDOUT_FILENO, &number, 1);

        // Print extra information if verbose is enabled
        if (verbose)
        {
            // print number using a different way
            printf("\tverbose: %c\n", number);
            // Increment number artificially
            number = number + 1;
        }

        // remove number
        returnKey();

        // Wait 5 seconds
        sleep(5);
    }

    return 0;
}