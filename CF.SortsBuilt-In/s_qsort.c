//
//  s_qsort.c
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/4/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#include "s_qsort.h"
#include "s_tools.h"
#include "s_callbacks.h"

/*
 *  MARK: do_qsort()
 */
void do_qsort(void) {
  printf("Fnuction: %s\n", __func__);

  int data[max_data];
  int * pdata;
  
  pdata = arrayinit(data);
  display(pdata, 10);
  qsort(&data, max_data, sizeof(data[0]), int_compare);
  display(pdata, 10);

  return;
}

/*
 *  MARK: do_qsort_r()
 */
void do_qsort_r(void) {
  printf("Fnuction: %s\n", __func__);
  
  int data[max_data];
  int * pdata;

  enum thnk { ASC = 0, DESC, };
  for (int thunk = ASC; thunk <= DESC; ++thunk) {
    switch (thunk) {
      default:
      case ASC:
        puts("Sort ascending");
        break;
        
      case DESC:
        puts("Sort descending");
        break;
    }

    pdata = arrayinit(data);
    display(pdata, 10);
    //  TODO: <<!!!>> Check MacOS/BSD vs. Linux/ISO implementations!
#ifdef __APPLE__
    qsort_r(&data, max_data, sizeof(data[0]), (void *) &thunk, int_compare_r);
#else
    qsort_r(&data, max_data, sizeof(data[0]), int_compare_r, (void *) &thunk);
#endif
    display(pdata, 10);
  }

  return;
}
