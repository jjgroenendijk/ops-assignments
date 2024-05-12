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
#include <stdio.h>   // printf
#include <stdlib.h>  // exit
#include <unistd.h>  // sleep
#include <signal.h>  // signal
#include <stdbool.h> // bool
#include <pthread.h> // pthread

#define SIGINT 2

volatile bool finishFlagRaised = false;

// Prototypes
void signalHandler(int signal);
void initSignalHandler(void);
void *producerThread(void *arg);
void *consumerThread(void *arg);

int main()
{
  // Initialize signal handler
  initSignalHandler();

  // Define threads
  pthread_t producerA, producerB, producerC, consumerD;

  // Create threads
  pthread_create(&producerA, NULL, producerThread, "A");
  pthread_create(&producerB, NULL, producerThread, "B");
  pthread_create(&producerC, NULL, producerThread, "C");
  pthread_create(&consumerD, NULL, consumerThread, "D");

  // Join threads
  pthread_join(producerA, NULL);
  pthread_join(producerB, NULL);
  pthread_join(producerC, NULL);
  pthread_join(consumerD, NULL);

  printf("\n\n\n"
         "Program finished!"
         "\n\n\n");
  
  return 0;
}

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

// Initialize signal handler
void initSignalHandler()
{
  struct sigaction sa;
  sa.sa_handler = signalHandler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);
}

// Producer thread function
void *producerThread(void *arg)
{
  // Print information about the consumer thread
  printf("Thread ID: %lu\t", (unsigned long)pthread_self());

  // Get the producer name and store it in a local variable
  char *producerName = (char *)arg;

  // Producer thread loop

  return NULL;
}

// Consumer thread function
void *consumerThread(void *arg)
{
  // Print information about the consumer thread
  printf("Thread ID: %lu\t", (unsigned long)pthread_self());

  // Execute every 15 seconds
  // Appends data to a file
  // Print data to stdout
  // Empty the queue

  // Get the consumer name and store it in a local variable
  char *consumerName = (char *)arg;

  // Consumer thread loop
  while (!finishFlagRaised)
  {
  }

  return NULL;
}