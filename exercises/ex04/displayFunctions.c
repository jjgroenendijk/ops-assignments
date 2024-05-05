#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "displayFunctions.h"
#include "syntaxCheck.h"

// Check the command-line parameters:
ErrCode SyntaxCheck(int argc, char **argv)
{
  ErrCode errCode = NO_ERR;

  if (argc < NUM_OF_PARS)
  {
    errCode = ERR_PARS;
  }
  else
  {
    // Test whether argument 3 (nice increment) contains a positive integer
    if (errCode == NO_ERR)
    {
      errCode = TestNr(argv[3]);
    }
  }
  return errCode;
}

// Print an error message:
void DisplayError(ErrCode errCode)
{
  switch (errCode)
  {
  case ERR_PARS:
    printf("\nNumber of command-line parameters is less than four.\n");
    break;
  case ERR_NR:
    printf("\nNumber of times is not a positive integer.\n");
    break;
  default:
    printf("\nUnknown error code!\n");
  }

  printf("\nCorrect syntax:\n");
  printf("  ./display <print type> <number of times> <print character>\n\n");
  printf("  first parameter: <print type>: e, p or w\n");
  printf("  second parameter: <number of times>: positive integer\n");
  printf("  third parameter: <nice increment>: a single integer\n");
  printf("  fourth parameter: <print character>: a variable amount of single characters seperated by a space\n");

  printf("\n"); // Newline at end
}