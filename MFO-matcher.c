/*
P1 Projekt
Gruppe: A310a
Projektperiode: Efteraarssemester 2020
Aalborg Universitet: Datalogi 1. semester
*/

/* Includes */
/* From standard library */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define HASH_ARRAY_SIZE 1000

/* Prototypes */
void to_upper (char *capitalise);
int hash(char *str);

/* For CuTest */
void RunAllTests(void);

/* Struct definitions */
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

struct matched_flora {
  char floraLatinName[40];
  char matchedFaunaLatinName[10][40];
};

struct fauna {
  char danishName[40];
  char latinName[40];
  enum roedliste endangerlvl;
  char *plants[100];

};


/* Custom header files */
#include "input.h"
#include "flora.h"
#include "fauna.h"
#include "CuTest.h"

/* Main */
int main(int argc, char const *argv[]) {
  if (argc > 1 && strcmp(argv[1], "--test") == 0) {
    RunAllTests();
  } else {
    struct area area = read_input();
    struct matched_flora *matched_flora;

    printf("P1 Projekt test\n");

    flora_database_and_matching(area);
    fauna_database_and_matching(matched_flora);
  }


  return EXIT_SUCCESS;
}

/* Function to capitalise latin name */
void to_upper(char *capitalise) {
    int i = 0;
    while (capitalise[i] != '\0'){
        capitalise[i] = toupper(capitalise[i]);
        i++;
    }
}

/* CuTests */
void TestStrToUpperAlpha(CuTest *tc) {
       char* input = strdup("hello world");
       to_upper(input);
       char* expected = "HELLO WORLD";
       CuAssertStrEquals(tc, expected, input);
}

void TestStrToUpperSpecialChars(CuTest *tc) {
       char* input = strdup("HeLoLo @@ ## test 1234");
       to_upper(input);
       char* expected = "HELOLO @@ ## TEST 1234";
       CuAssertStrEquals(tc, expected, input);
}

CuSuite* StrUtilGetSuite() {
   CuSuite* suite = CuSuiteNew();
   SUITE_ADD_TEST(suite, TestStrToUpperAlpha);
   SUITE_ADD_TEST(suite, TestStrToUpperSpecialChars);
   return suite;
}
/* End CUTests */


/* Hash function djb2 taken from http://www.cse.yorku.ca/~oz/hash.html */
int hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  /* Hash is trimmed to the HASHTABLE_SIZE */
  hash %= FLORA_HASH_ARRAY_SIZE;

  return hash;
}
