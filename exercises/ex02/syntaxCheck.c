/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.4
 * Datum:        2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  definitions of test functions for display.c
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "syntaxCheck.h"


// Test whether an argument is one character long and has the correct value (e,p,w):
ErrCode TestType(char *printMethod) {
  ErrCode fout = NO_ERR;
  
  // Add the missing code
  printf("\nChosen printmethod: %s\n", printMethod);

  // check if printMethod is equal to e, p or w
  if (strlen(printMethod) != 1) {
    fout = ERR_TYPE;
  } else {
    if (printMethod[0] != 'e' && printMethod[0] != 'p' && printMethod[0] != 'w') {
      fout = ERR_TYPE;
    }
  }

  return fout;
}


// Test whether an argument contains a non-negative number:
ErrCode TestNr(char *numberOfTimes) {
  ErrCode fout = NO_ERR;
  
  // Add the missing code
  
  return fout;
}


// Test whether an argument contains only one character:
ErrCode TestChar(char *printChar) {
  ErrCode fout = NO_ERR;
  
  // Add the missing code
  if (strlen(printChar) != 1) {
    fout = ERR_CHAR;
  }

  return fout;
}
