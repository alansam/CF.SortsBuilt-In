//
//  s_callbacks.c
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/5/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#include "s_callbacks.h"

//  MARK: - Sort comparitor callbacks
/*
 *  Custom comparison function that  compares 'int' values through pointers
 *  passed by qsort(3).
 *  @see: https://www.freebsd.org/cgi/man.cgi?query=qsort&sektion=3&manpath=freebsd-release-ports
 */
int int_compare(void const * p1, void const * p2) {

  int left =  *(int const *) p1;
  int right = *(int const *) p2;

  return ((left > right) - (left < right));
}

// If you want to use a single compare function that changes behavior based on
// another argument, you can use qsort_r() and add an additional parameter to your
// comparison function (a void* variable called "thunk").
//
// Also, if your compare function changes a global variable and you could have
// multiple threads running qsort and touching that same global variable at the
// same time---there could be problems! qsort_r() would allow you to use one
// compare function, but to tell each thread what data it should be working with
// (besides the actual data that is getting sorted).
//
//  TODO: <<!!!>> Check MacOS/BSD vs. Linux/ISO implementations!
#ifdef __APPLE__
int int_compare_r(void * thunkIn, void const * aIn, void const * bIn) {
#else
int int_compare_r(void const * aIn, void const * bIn, void * thunkIn) {
#endif

  int a     = *((int *) aIn);
  int b     = *((int *) bIn);
  int thunk = *((int *) thunkIn);
  int returnVal;

  if (thunk == 0) {
    //  sort ascending
    if (a < b)      { returnVal = -1; }
    else if (a > b) { returnVal = 1; }
    else            { returnVal = 0;}
  }
  else {
    //  sort descending
    if(a > b)       { returnVal = -1; }
    else if(a < b)  { returnVal = 1; }
    else            { returnVal = 0; }
  }

  return returnVal;
}
