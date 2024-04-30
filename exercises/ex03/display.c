#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "displayFunctions.h"

int main(int argc, char *argv[])
{
  unsigned long int numOfTimes = strtoul(argv[2], NULL, 10); // String to unsigned long
  unsigned long int niceIncr = (int)strtoul(argv[3], NULL, 10);
  char printMethod, printChar;
  ErrCode err;

  // Check the command-line parameters
  err = SyntaxCheck(argc, argv);
  if (err != NO_ERR)
  {
    DisplayError(err);
  }

  printMethod = argv[1][0];

  // Determine the amount of characters that will be printed on screen
  unsigned long int numOfChar = argc - 4;
  printf("numOfChar: %lu\n", numOfChar);

  // loop over every iChild (which covers the number of different print characters)
  for (int iChild = 0; iChild < numOfChar; iChild++)
  {

    // Start forking children here:
    pid_t pid = fork();

    if (pid == 0)
    {
      // Child process
      // printf("child process pid: %i\n", getpid());

      // show the iteration, the nice value result and the character to print
      printf("%i %lu %c\n", iChild, iChild * niceIncr, argv[iChild + 4][0]);
      exit(0);
    }
    else
    {
      // Parent process
      printf("parent process pid: %i\n", getpid());
    }
  }
  return 0;
}