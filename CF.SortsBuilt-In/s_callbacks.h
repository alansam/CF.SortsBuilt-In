//
//  s_callbacks.h
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/5/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#pragma once
#ifndef s_callbacks_h
#define s_callbacks_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>


//  MARK: sorting callback prototypes
int int_compare(void const * p1, void const * p2);

//  TODO: <<!!!>> Check MacOS/BSD vs. Linux/ISO implementations!
#ifdef __APPLE__
int int_compare_r(void * thunkIn, void const * aIn, void const * bIn);
#else
int int_compare_r(void const * aIn, void const * bIn, void * thunkIn);
#endif

#endif /* s_callbacks_h */
