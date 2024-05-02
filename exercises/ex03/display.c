#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "displayFunctions.h"

int main(int argc, char *argv[])
{
  // Declare needed variables. Mostly for interpreting argv arguments
  char printMethod = argv[1][0];
  unsigned long int numOfTimes = strtoul(argv[2], NULL, 10);
  unsigned long int niceIncr = strtoul(argv[3], NULL, 10);
  unsigned long int numOfChar = argc - 4;
  char printChar;
  ErrCode err;

  // Print global variables for a sanity check
  printf("printMethod: %c\n"
         "numOfTimes: %lu\n"
         "niceIncr: %lu\n"
         "numOfChar: %lu\n\n",
         printMethod, numOfTimes, niceIncr, numOfChar);

  // Check the command-line parameters
  err = SyntaxCheck(argc, argv);
  if (err != NO_ERR)
  {
    DisplayError(err);
  }
  else
  {

    // loop over every iChild (which covers the number of different print characters)
    for (int iChild = 0; iChild < numOfChar; iChild++)
    {

      // Start forking children here:
      pid_t pid = fork();

      // Child process
      if (pid == 0)
      {
        // Calculate new nice value, set the new nice value and print to console
        int newNiceValue = iChild * niceIncr;
        int niceValue = nice(newNiceValue);
        printf("\tnice: %i", niceValue);

        // Find and print the character
        printChar = argv[iChild + 4][0];
        PrintCharacters(printMethod, numOfTimes, printChar);

        exit(0);
      }

      // Parent process
      if (pid != 0)
      {

        // Wait for all child processes to finish and print a new line
        int status;
        while ((pid = wait(&status)) != -1) {;}
        printf("\n");
      }
    }
  }
  return 0;
}