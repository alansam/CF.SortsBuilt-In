//
//  s_tools.c
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/4/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#include "s_tools.h"

//  MARK: Constants
size_t const max_data = MAX_DATA;
size_t const max_str = MAX_STR;

static
char const * sstrings[max_str] = {
  "XYZZY", "PLUGH", "PLOVER",
  "Xyzzy", "Plugh", "Plover",
  "xyzzy", "plugh", "plover",
};
static
size_t sstrings_l = sizeof(sstrings) / sizeof(sstrings[0]);

//  MARK: - Helper functions
/*
 *  MARK: setupstrings()
 */
size_t setupstrings(char const * strings[max_str]) {

  for (size_t s_ = 0; s_ < max_str; ++s_) {
    strings[s_] = sstrings[s_];
  }

  return sstrings_l;
}

/*
 *  MARK: displaystrings()
 */
void displaystrings(char const * strings[max_str], size_t cols) {

  for (size_t i_ = 0; i_ < max_str; ++i_) {
    printf("%10s%c",
           strings[i_],
           (i_ % cols == cols - 1 || i_ == max_str - 1) ? '\n' : ' ');
  }
  putchar('\n');

  return;
}

/*
 *  MARK: arrayinit()
 */
int * arrayinit(int data[max_data]) {

  int rupper = 200;
  int rlower = -200;
  for (size_t e_ = 0; e_ < max_data; ++e_) {
    long rn = (random() % (rupper - rlower - 1)) + rlower;
    data[e_] = (int) rn;
  }

  return data;
}

/*
 *  MARK: display()
 */
void display(int data[max_data], size_t cols) {

  for (size_t i_ = 0; i_ < max_data; ++i_) {
    printf("%6d%c",
       data[i_],
       (i_ % cols == cols - 1 || i_ == max_data - 1) ? '\n' : ' ');
  }
  putchar('\n');

  return;
}
