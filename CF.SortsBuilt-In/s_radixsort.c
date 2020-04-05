//
//  s_radixsort.c
//  CF.SortsBuilt-In
//
//  Created by Alan Sampson on 4/5/20.
//  Copyright © 2020 Alan @ FreeShell. All rights reserved.
//

#include "s_radixsort.h"
#include "s_tools.h"

//  MARK: - Definitions
static
char const * const alpha = "abcdefghijklmnopqrstuvwxyz";
static
char const * const Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
 *  MARK: do_radixsort()
 */
void do_radixsort(void) {
  printf("Fnuction: %s\n", __func__);

  unsigned char table[UCHAR_MAX + 1];
  for (size_t c_ = 0; c_ < UCHAR_MAX + 1; ++c_) {
    table[c_] = c_;
  }

  for (size_t c_ = 0; c_ < strlen(alpha); ++c_) {
    char ac = alpha[c_];
    char Ac = Alpha[c_];
    table[ac] = Ac;
  }

  srdxsrt fns[] = {
    { .pfunc = radixsort,  .name = "radixsort  - radix sort", },
    { .pfunc = sradixsort, .name = "sradixsort - stable radix sort", },
  };
  size_t fns_l = sizeof(fns) / sizeof(*fns);

  unsigned char * ptables[] = {
    NULL, table,
  };
  size_t ptables_l = sizeof(ptables) / sizeof(*ptables);

  enum tbl { ASC = 0x00, DESC, };

  for (size_t v_ = 0; v_ < ptables_l; ++v_) {
    printf("Pass %2zu\n", v_);
    unsigned char * ptable;
    ptable = ptables[v_];

    for (unsigned order = ASC; order <= DESC; ++order) {
      unsigned endbyte;

      switch (order) {
        default:
        case ASC:
          puts("Ascending");
          endbyte = 0x00;
          break;
        
        case DESC:
          puts("Descending");
          endbyte = 0xff;
          break;
      }

      for (size_t f_ = 0; f_ < fns_l; ++f_) {
        srdxsrt zrdxort = fns[f_];
        rdxsrt frdxort = zrdxort.pfunc;
        printf("%s\n", zrdxort.name);

        char const * strings[max_str];
        size_t strings_l = setupstrings(strings);

        size_t cols = 3;
        displaystrings(strings, cols);

        unsigned char const ** pstrings = (unsigned char const **) strings;
        frdxort(pstrings, (int) strings_l, ptable, endbyte);

        displaystrings(strings, cols);
      }
    }
  }

  return;
}
