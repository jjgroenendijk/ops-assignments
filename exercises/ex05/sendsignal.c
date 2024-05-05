/*

    Write a program called sendsignal, which sends signal 25 to a given PID every three seconds.
    Use the functions kill() (see man 2 kill) and sleep().
    The program should obtain the PID of getsignal from the command line:

        $ ./sendsignal <PID of getsignal>

*/

#include <stdio.h>
#include <signal.h> // kill()
#include <unistd.h> // sleep()
#include <stdlib.h> // atoi(), system()

void clearTerminal()
{
    system("clear");
}

int main(int argc, char *argv[])
{
    int pid;

    if (argc <= 1)
    {
        // Please enter a valid PID
        printf("Please enter a valid PID\n");
        return 1;
    }
    else
    {
        pid = atoi(argv[1]);
    }

    printf("Sending signal 25 to PID: %d\n", pid);

    while (1)
    {
        kill(pid, 25);
        sleep(3);
    }

    return 0;
}