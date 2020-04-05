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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

//  MARK: - Definitions
static
size_t const max_data = 400;
static
size_t const max_str = 9;

void do_qsort(void);
void do_qsort_r(void);
void do_heapsort(void);
void do_mergesort(void);
void do_radixsort(void);
int * arrayinit(int data[max_data]);
void display(int data[max_data], size_t cols);
size_t setupstrings(char const * strings[max_str]);
void displaystrings(char const * strings[max_str], size_t cols);

static
int int_compare(void const * p1, void const * p2);

//  TODO: <<!!!>> Check MacOS/BSD vs. Linux/ISO implementations!
#ifdef __APPLE__
static
int int_compare_r(void * thunkIn, void const * aIn, void const * bIn);
#else
static
int int_compare_r(void const * aIn, void const * bIn, void * thunkIn);
#endif

//  test data
static
char const * sstrings[max_str] = {
  "XYZZY", "PLUGH", "PLOVER",
  "Xyzzy", "Plugh", "Plover",
  "xyzzy", "plugh", "plover",
};
static
size_t sstrings_l = sizeof(sstrings) / sizeof(sstrings[0]);

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
 *  MARK: do_heapsort()
 */
void do_heapsort(void) {
  printf("Fnuction: %s\n", __func__);

  int data[max_data];
  int * pdata;
  
  pdata = arrayinit(data);
  display(pdata, 10);
  heapsort(&data, max_data, sizeof(data[0]), int_compare);
  display(pdata, 10);

  return;

}

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

/*
 *  MARK: do_radixsort()
 */
void do_radixsort(void) {
  printf("Fnuction: %s\n", __func__);

  srdxsrt fns[] = {
    { .pfunc = radixsort,  .name = "radixsort  - radix sort", },
    { .pfunc = sradixsort, .name = "sradixsort - stable radix sort", },
  };
  size_t fns_l = sizeof(fns) / sizeof(*fns);

  unsigned char table[UCHAR_MAX + 1];
  for (size_t c_ = 0; c_ < UCHAR_MAX + 1; ++c_) {
    table[c_] = c_;
  }

  char const * alpha = "abcdefghijklmnopqrstuvwxyz";
  char const * Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (size_t c_ = 0; c_ < strlen(alpha); ++c_) {
    char ac = alpha[c_];
    char Ac = Alpha[c_];
    table[ac] = Ac;
  }

  unsigned char * ptables[] = {
    NULL, table,
  };
  size_t ptables_l = sizeof(ptables) / sizeof(*ptables);

  enum tbl { ASC = 0x00, DESC, };

  for (size_t f_ = 0; f_ < fns_l; ++f_) {
    srdxsrt zrdxort = fns[f_];
    rdxsrt frdxort = zrdxort.pfunc;
    printf("%s\n", zrdxort.name);

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

//        char const * strings[] = {
//          "XYZZY", "PLUGH", "PLOVER",
//          "Xyzzy","Plugh","Plover",
//          "xyzzy","plugh","plover",
//        };
//        size_t strings_l = sizeof(strings) / sizeof(strings[0]);

        char const * strings[max_str];
        size_t strings_l = setupstrings(strings);

        size_t cols = 3;
//        for (size_t i_ = 0; i_ < strings_l; ++i_) {
//          printf("%10s%c",
//                 strings[i_],
//                 (i_ % cols == cols - 1 || i_ == (size_t) strings - 1) ? '\n' : ' ');
//        }
//        putchar('\n');
        displaystrings(strings, cols);

        unsigned char const ** pstrings = (unsigned char const **) strings;
        frdxort(pstrings, (int) strings_l, ptable, endbyte);

//        for (size_t i_ = 0; i_ < strings_l; ++i_) {
//          printf("%10s%c",
//                 strings[i_],
//                 (i_ % cols == cols - 1 || i_ == (size_t) strings - 1) ? '\n' : ' ');
//        }
//        putchar('\n');
        displaystrings(strings, cols);
      }
    }
  }

  return;
}

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
           (i_ % cols == cols - 1 || i_ == (size_t) strings - 1) ? '\n' : ' ');
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
       (i_ % cols == cols - 1 || i_ == (size_t) data - 1) ? '\n' : ' ');
  }
  putchar('\n');

  return;
}

/*
 *  Custom comparison function that  compares 'int' values through pointers
 *  passed by qsort(3).
 *  @see: https://www.freebsd.org/cgi/man.cgi?query=qsort&sektion=3&manpath=freebsd-release-ports
 */
static
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
static
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
