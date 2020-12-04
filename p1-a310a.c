/*
P1 Projekt
Gruppe: A310a
Projektperiode: Efteraarssemester 2020
Aalborg Universitet: Datalogi 1. semester
*/

/* Includes */
// From standard library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Struct definitions
struct area {
  int heaviness;
  int light;
  int pH;
  int nutrient;
  int moistness;
  int totalArea;
  int mfoArea;
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
  struct flora *plants;
};


// Custom header files
#include "input.h"
#include "flora.h"
#include "fauna.h"

/* Prototypes */



/* Main */
int main(int argc, char const *argv[]) {

  struct area area = read_input();

  printf("P1 Projekt test\n");

  printFloraTest(area);
  printFaunaTest();

  return EXIT_SUCCESS;
}
