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
    printf("argc: %i\n", argc);
    printf("NUM_OF_PARS: %i", NUM_OF_PARS);
    errCode = ERR_PARS;
  }
  else
  {
    errCode = TestType(argv[1]); // Test whether argument 1 has the correct value (print type)

    // Test whether argument 2 contains a positive integer (number of times)
    if (errCode == NO_ERR)
    {
      errCode = TestNr(argv[2]);
    }

    // Test whether argument 3 contains a positive integer (number of times)
    if (errCode == NO_ERR)
    {
      errCode = TestNr(argv[3]);
    }

    // Test whether argument 4 contains only one character (print character)
    if (errCode == NO_ERR)
    {

      // Calculate amount of characters to test
      int charsToTest = argc - 4;
      printf("testing %i characters\n", charsToTest);

      // Loop through all characters and check each one
      for (int i = 0; (i < charsToTest) && (errCode == NO_ERR); i++)
      {
        errCode = TestChar(&argv[i + 4][0]);
      }
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
  case ERR_TYPE:
    printf("\nUnknown print type.\n");
    break;
  case ERR_NR:
    printf("\nNumber of times is not a positive integer.\n");
    break;
  case ERR_CHAR:
    printf("\nPrint character contains more than one character.\n");
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

// Print chacacter printChar numberOfTimes times using method printMethod:
void PrintCharacters(char printMethod, unsigned long numberOfTimes, char printChar)
{
  unsigned long index = 0;
  char echoCommand[] = "/bin/echo -n  ";

  switch (printMethod)
  {
  case 'e':
    echoCommand[13] = printChar; // Put character to be printed in string
    for (index = 0; index < numberOfTimes; index++)
    {
      system(echoCommand);
    }
    break;
  case 'p':
    for (index = 0; index < numberOfTimes; index++)
    {
      printf("%c", printChar);
    }
    break;
  case 'w':
    for (index = 0; index < numberOfTimes; index++)
    {
      write(1, &printChar, 1);
    }
    break;
  default:
    printf("INTERNAL ERROR: Unknown print type:  %s.  This should not happen!\n", &printMethod);
  }
}
