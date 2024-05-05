#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "displayFunctions.h"

int main(int argc, char *argv[])
{
  ErrCode err;

  // Check the command-line parameters
  err = SyntaxCheck(argc, argv);
  if (err != NO_ERR)
  {
    DisplayError(err);
  }

  // Continue if no errors have been found in the arguments
  else
  {
    // Declare variables after the syntax has been checked
    char printMethod = argv[1][0];
    unsigned long int numOfTimes = strtoul(argv[2], NULL, 10);
    unsigned long int niceIncr = strtoul(argv[3], NULL, 10);
    unsigned long int numOfChar = argc - 4;
    int waitIncrement = 0;

    // Print global variables for a sanity check
    printf("SANITY CHECK DECLARED VARIABLES:\n"
           "printMethod: %c\n"
           "numOfTimes: %lu\n"
           "niceIncr: %lu\n"
           "numOfChar: %lu\n\n",
           printMethod, numOfTimes, niceIncr, numOfChar);

    // loop over every iChild (which covers the number of different print characters)
    for (int iChild = 0; iChild < (argc - 4); iChild++)
    {

      // Calculate new nice value, set the new nice value and retrieve actual current Nice Value
      int newNiceValue = iChild * niceIncr;
      nice(newNiceValue);
      int currentNiceValue = getpriority(PRIO_PROCESS, 0);

      // Start forking children here:
      pid_t pid = fork();

      // Child process
      if (pid == 0)
      {
        // Set letter to print
        char *printMethodPointer = argv[1];
        char *numOfTimesPointer = argv[3];
        char *printCharPointer = argv[iChild + 4];

        // Starting threads
        printf("Process ID: %i", getpid());

        // execl() to exercise 2
        int runExec = execl(
            "../ex02/display",
            "../ex02/display",
            printMethodPointer,
            numOfTimesPointer,
            printCharPointer,
            NULL);

        if (runExec == -1)
        {
          perror("execl failed!\n");
          exit(EXIT_FAILURE);
        }
      }

      // Parent process
      if (pid != 0)
      {

        // Wait for all child processes to finish
        int status;
        while ((pid = wait(&status)) != -1)
        {
          // Increment the waitIncrement
          waitIncrement++;
        }
      }

      // Print the message after all child processes have finished
      if (waitIncrement == numOfChar)
      {
        printf("Threads have finished\n");
      }
    }
  }
  return 0;
}