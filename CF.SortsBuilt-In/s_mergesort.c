//
//  s_mergesort.c
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/5/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#include "s_mergesort.h"
#include "s_tools.h"
#include "s_callbacks.h"

/*
 *  MARK: do_mergesort()
 */
void do_mergesort(void) {
  printf("Fnuction: %s\n", __func__);
  
  int data[max_data];
  int * pdata;
  
  pdata = arrayinit(data);
  display(pdata, 10);
  mergesort(&data, max_data, sizeof(data[0]), int_compare);
  display(pdata, 10);

  return;
}
