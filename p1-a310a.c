/*
P1 Projekt
Gruppe: A310a
Projektperiode: Efteraarssemester 2020
*/

/* Includes */
// From standard library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define HASH_ARRAY_SIZE 1000

/* Prototypes */
int hash(char *str);

// Struct definitions
struct area {
  int heaviness;
  int light;
  int pH;
  int nutrient;
  int moistness;
  double totalArea;
  double mfoArea;
};

enum mfoTypes {
  mfoBreammer,
  mfoBrak,
  mfoBestoeverbrak
};

enum roedliste {
  RE,
  CR,
  EN,
  VU,
  NT,
  DD,
  LC,
  NA,
  NE
};

struct flora {
  char danishName[40];
  char latinName[40];
  int lifespan;
  int heaviness;
  int light;
  int pH;
  int nutrient;
  int moistness;
  enum mfoTypes mfoType;
};

struct fauna {
  char danishName[40];
  char latinName[40];
  enum roedliste endangerlvl;
  char plant[100][40];
    
};


// Custom header files
#include "input.h"
#include "flora.h"
#include "fauna.h"

/* Main */
int main(int argc, char const *argv[]) {

  struct area area = read_input();

  printf("P1 Projekt test\n");

  printFloraTest();
  printFaunaTest();

  return EXIT_SUCCESS;
}

/* Hash function djb2 taken from http://www.cse.yorku.ca/~oz/hash.html */
int hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        /* Hash is trimmed to the HASHTABLE_SIZE */
    hash %= HASH_ARRAY_SIZE;

    return hash;
}
