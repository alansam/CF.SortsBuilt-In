//
//  sorter.c
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/4/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//
//  MARK: - Reference:
//  @see: https://www.freebsd.org/cgi/man.cgi?query=qsort&sektion=3&manpath=freebsd-release-ports
//

#include "sorter.h"
#include "s_qsort.h"
#include "s_heapsort.h"
#include "s_mergesort.h"
#include "s_radixsort.h"
#include "s_tools.h"
#include "s_callbacks.h"


//  MARK: structures, typedefs, etc.

//  MARK: - Implementation
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  printf("CF.SortsBuilt-In\n");

  puts("Doing qsort");
  do_qsort();

  puts("Doing heapsort");
  do_heapsort();

  puts("Doing mergesort");
  do_mergesort();
  
  puts("Doing qsort_r");
  do_qsort_r();
  
  puts("Doing radixsort");
  do_radixsort();

  return EXIT_SUCCESS;
}
