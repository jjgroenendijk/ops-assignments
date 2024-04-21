/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.4
 * Datum:        2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  definitions of test functions for display.c
 ******************************************************************************/

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntaxCheck.h"

// Test whether an argument is one character long and has the correct value (e,p,w):
ErrCode TestType(char *printMethod)
{
  ErrCode fout = NO_ERR;

  // Check if printMethod is not equal to 1 character
  if (!(strlen(printMethod) == 1))
  {
    //printf("\nWrong amount of input letters as first argument!\n");
    fout = ERR_TYPE;
  }

  // Check if printMethod is not equal to character e, p or w
  if (!((strcmp(printMethod, "e") == 0) || (strcmp(printMethod, "p") == 0) || (strcmp(printMethod, "w") == 0)))
  {
    //printf("\nWrong input letter as first argument!\n");
    fout = ERR_TYPE;
  }

  return fout;
}

// Test whether an argument contains a non-negative number:
ErrCode TestNr(char *numberOfTimes)
{
  ErrCode fout = NO_ERR;

  int num = atoi(numberOfTimes);
  if (!(num >= 0))
  {
    fout = ERR_NR;
  }

  return fout;
}

// Test whether an argument contains only one character:
ErrCode TestChar(char *printChar)
{
  ErrCode fout = NO_ERR;

  int printCharIndex = 0;

  while (printChar[printCharIndex] != '\0')
  {
    //printf("printchar pos: %i data: %c\n", printCharIndex, printChar[printCharIndex]);
    if (printCharIndex > 0)
    {
      fout = ERR_CHAR;
      break;
    }
    printCharIndex++;
  }

  return fout;
}
