//
//  s_mergesort.h
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/5/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#pragma once
#ifndef s_mergesort_h
#define s_mergesort_h

#if !defined(__APPLE__) && !defined(_GNU_SOURCE)
# define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

//  MARK: function prototypes
void do_mergesort(void);

#endif /* s_mergesort_h */
