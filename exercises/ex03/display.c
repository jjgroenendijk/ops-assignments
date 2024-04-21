/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "displayFunctions.h"

int main(int argc, char *argv[]) {
  unsigned long int numOfTimes;
  char printMethod, printChar;
  ErrCode err;

  unsigned long int numOfChar = argc - 4;
  printf("numOfChar: %lu\n", numOfChar);
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message
  } else {
    printMethod = argv[1][0];
    numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long

    int qq = 0;

    while (argv[3][qq] != '\0')
    {
      printChar = argv[3][qq];
      PrintCharacters(printMethod, numOfTimes, printChar);
      qq++;
    }

    //PrintCharacters(printMethod, numOfTimes, printChar);  // Print character printChar numOfTimes times using method printMethod
  }
  
  printf("\n");  // Newline at end
  return 0;
}
