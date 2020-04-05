//
//  s_tools.h
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/4/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#pragma once
#ifndef s_tools_h
#define s_tools_h

#if !defined(__APPLE__) && !defined(_GNU_SOURCE)
# define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

#define MAX_DATA 400
#define MAX_STR 9

//  MARK: Constants
extern
size_t const max_data;
extern
size_t const max_str;

//  MARK: function prototypes
int * arrayinit(int data[max_data]);
void display(int data[max_data], size_t cols);
size_t setupstrings(char const * strings[max_str]);
void displaystrings(char const * strings[max_str], size_t cols);

#endif /* s_tools_h */
