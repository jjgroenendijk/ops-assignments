/*

  Program description:
    1. a thread that writes data (i.e. a node) to the shared queue every 2 seconds. This is a producer thread;
    2. a producer thread that writes data to the shared queue every 3 seconds;
    3. a producer thread that writes data to the shared queue every 4 seconds;
      • you should use the same thread function for all three producer threads. Hint: use different arguments when starting your threads to pass data and production intervals;
      • the producer threads do not produce screen output.
    4. a consumer thread that reads data from the shared queue every 15 seconds, appends these data to a file, prints them to stdout and empties the queue. In the interval between two consumer iterations, no output is shown on the screen.

  Requirements:
    • Ensure that the data are different for each thread, so that we can recognise which data come from which producer.
      Hint: pass these as arguments when starting your threads.
    •  Use the C function sleep() in a loop to generate the desired production and consumption intervals. Hint: these loops must be in the thread functions.
    • Use a mutex or mutexes to guard the critical actions. How many mutexes do you need?
    • When Ctrl-C is pressed, all threads must finish their last cycle, rather than terminate immediately. In the end, the consumer saves the last data produced and also quits. This will require a shared variable that is accessible to all threads.
    • The main() function in sharedQueue.c only installs the SHR and creates and joins the four threads.
      Hint: you should do most of your coding in sharedQueue.c (and you will have to change it drastically), and only very little in the other source files.

*/

#include "Queue.h"
#include <stdio.h> // printf
#include <stdlib.h>
#include <unistd.h>  // sleep
#include <signal.h>  // signal
#include <stdbool.h> // bool

#define SIGINT 2

bool finishFlagRaised = false;

// Signal handler for CTRL-C
// To make sure all threads finish their last cycle
void signalHandler(int signal)
{
  if (signal == SIGINT)
  {
    printf("\n"
           "CTRL-C pressed\n"
           "Raising the finish flag!\n");
    finishFlagRaised = true;
  }
}

int main()
{
  // Signal handler for CTRL-C
  // signal(SIGINT, signalHandler);
  struct sigaction sa;
  sa.sa_handler = signalHandler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(SIGINT, &sa, NULL) == -1)
  {
    perror("sigaction");
    return 1;
  }

  int timeTick = 0;

  while ((timeTick < 15) && (finishFlagRaised == false))
  {
    // Show current time tick
    printf("Time tick: %d\t", timeTick);

    // Producer thread A
    // Write data to queue every 2 seconds
    if (timeTick % 2 == 0)
    {
      printf("Producer thread A\t");
    }

    // Producer thread B
    // Write data to queue every 3 seconds
    if (timeTick % 3 == 0)
    {
      printf("Producer thread B\t");
    }

    // Producer thread C
    // Write data to queue every 4 seconds
    if (timeTick % 4 == 0)
    {
      printf("Producer thread C\t");
    }

    // Consumer thread
    // Read data from queue every 15 seconds
    if (timeTick % 15 == 0)
    {
      printf("Consumer thread\t");

      // Append data to file

      // Print data to stdout

      // Empty the queue
    }

    // sleep for 1 second
    sleep(1);

    // Increment timeTick
    if (timeTick == 14)
    {
      timeTick = 0;
    }
    else
    {
      timeTick++;
    }

    printf("\n");
  }

  return 0;
}
