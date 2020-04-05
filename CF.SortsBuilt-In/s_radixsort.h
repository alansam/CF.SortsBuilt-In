//
//  s_radixsort.h
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/5/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#ifndef s_radixsort_h
#define s_radixsort_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

/*
 *  MARK: radixsort - function pointer
 */
typedef
int (*rdxsrt)(const unsigned char ** __base,
              int __nel,
              const unsigned char * __table,
              unsigned __endbyte);

/*
 *  MARK: structure srdxsrt
 */
struct srdxsrt {
  rdxsrt pfunc;
  char name[40];
};
typedef struct srdxsrt srdxsrt;

//  MARK: function prototypes
void do_radixsort(void);

#endif /* s_radixsort_h */
