/*

    Write a program called getsignal which prints a single-digit number (0–9) unbuffered to stdout every second.
    Use the write() system call for unbuffered output and print all numbers to the same line.
    You can use the sleep() function (see man 3 sleep) to generate the wait time of 1s.
    The program getsignal keeps printing the same number, until it receives signal number 25,
    upon which the number it prints will be increased by one.
    If the number was 9, it will become 0. Use the POSIX standard (sigaction()).
    Hint: use characters for your numbers (’1’ etc.). Note that ’5’+1 yields ’6’.

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>  // write(), sleep()
#include <stdlib.h>  // system()
#include <stdbool.h> // bool

bool debug = false;

volatile char number = '0';

void signalHandler(int signal)
{
    if (debug)
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
    // // Should not be used according to man signal
    // signal(25, signalHandler);

    struct sigaction action;
    action.sa_handler = signalHandler;
    sigaction(25, &action, NULL);

    clearTerminal();

    printf("Process ID: %d\n", getpid());

    while (1)
    {
        // Write number to stdout unbuffered
        write(STDOUT_FILENO, &number, 1);

        // Print extra information if debug is enabled
        if (debug)
        {
            // print number using a different way
            printf("\tdebug: %c\n", number);
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