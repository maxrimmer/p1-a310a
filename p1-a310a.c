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


// Custom header files
#include "input.h"
#include "flora.h"
#include "fauna.h"

/* Prototypes */



/* Main */
int main(int argc, char const *argv[]) {

  struct area area = read_input();

  printf("P1 Projekt test\n");

  printFloraTest();
  printFaunaTest();

  return EXIT_SUCCESS;
}
