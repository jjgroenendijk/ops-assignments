/*

  To do:
    - appendFile function
    - Mutex implementation
    - Check if queue is empty
    - Check for memory leaks
    - Random number with fixed width

*/

// Libraries
#include "Queue.h"
#include <stdio.h>   // printf
#include <stdlib.h>  // exit
#include <unistd.h>  // sleep
#include <signal.h>  // signal
#include <stdbool.h> // bool
#include <pthread.h> // pthread
#include <string.h>  // strcpy
#include <time.h>    // time (random number generator)

// Constants
#define SIGINT 2

// Global variables
volatile bool continueFlag = true;

typedef struct queueArgs
{
  int sleepTime;
  char *producerName;
} queueArgs_t;

// Initialize a data queue
data_t data = {1, "Hello queue"};
queue_t queue = {NULL}; // Note: element of queue = NULL

// Prototypes
void signalHandler(int signal);
void initSignalHandler(void);
void *producerThread(void *arg);
void *consumerThread(void *arg);
void appendFile(queue_t *queue);

int main()
{
  // Seed the random number generator
  srand(time(NULL));

  // Initialize signal handler
  initSignalHandler();

  // Create a queue
  createQueue(&queue, data);

  // Define threads
  pthread_t producerA, producerB, producerC, consumerD;

  // Define arguments for the threads (sleeptime and thread name)
  queueArgs_t queueArgsA = {2, "A"};
  queueArgs_t queueArgsB = {3, "B"};
  queueArgs_t queueArgsC = {4, "C"};
  queueArgs_t queueArgsD = {15, "D"};

  // Create threads
  pthread_create(&producerA, NULL, producerThread, &queueArgsA);
  pthread_create(&producerB, NULL, producerThread, &queueArgsB);
  pthread_create(&producerC, NULL, producerThread, &queueArgsC);
  pthread_create(&consumerD, NULL, consumerThread, &queueArgsD);

  // Join threads
  pthread_join(producerA, NULL);
  pthread_join(producerB, NULL);
  pthread_join(producerC, NULL);
  pthread_join(consumerD, NULL);

  printf("\n"
         "Program finished!"
         "\n");

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
    continueFlag = false;
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
  // Cast the argument to queueArgs_t
  queueArgs_t *queueArgs = (queueArgs_t *)arg;

  // Get the producer name and sleep time from the argument
  char *producerName = queueArgs->producerName;
  int sleepTime = queueArgs->sleepTime;

  // Producer thread loop
  while (continueFlag)
  {
    // Generate a random number between 0 and 999999
    int random = rand() % 999999;

    // Create a new data node and enqueue it
    data = (data_t){random, *producerName};
    pushQueue(&queue, data);

    // Sleep for the specified time
    sleep(sleepTime);
  }

  return NULL;
}

// Consumer thread function
void *consumerThread(void *arg)
{
  // Cast the argument to queueArgs_t
  queueArgs_t *queueArgs = (queueArgs_t *)arg;

  // Get the producer name and sleep time from the argument
  char *producerName = queueArgs->producerName;
  int sleepTime = queueArgs->sleepTime;

  // Consumer thread loop
  while (continueFlag)
  {
    // Append all data to a file
    appendFile(&queue);

    // Print data to stdout
    showQueue(&queue);

    // SOMETHING GOES WRONG HERE. THE QUEUE IS NOT EMPTIED OR DATA SEGFAULTS. PROBABLY NEEDS A MUTEX

    // Empty the queue
    while (!(emptyQueue(&queue)))
    {
      popQueue(&queue);
    }

    // Sleep for 15 seconds
    sleep(sleepTime);
  }

  return NULL;
}

// Write queue data to a file
void appendFile(queue_t *queue)
{
  // Get the last node in the queue
  const node_t *nextN = queue->lastNode;

  // Create a file if it doesn't exist. Open it in append mode
  FILE *file = fopen("queueData.txt", "a");

  // Check if the file is open
  if (file == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  // Check if the queue is empty
  if (nextN == NULL)
  {
    printf("Queue is empty, last node is %p\n", (void *)queue->lastNode);
  }

  // Write queue data to file as long as the queue is not empty
  else
  {
    do
    {
      nextN = nextN->nextNode;
      fprintf(file, "pNode = %p  Data = '%d' '%s'  nextN = %p\n",
              (void *)nextN, nextN->data.intVal, nextN->data.text, (void *)nextN->nextNode);
    } while (nextN != queue->lastNode);
  }

  // Close the file
  fclose(file);
}
