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
#define MAX_NUMBER_OF_MATCHES 100
#define MAX_NAME_LENGTH 40
#define MAX_FLORA_PER_FAUNA 10

/* Prototypes */
void to_upper (char *capitalise);
int hash(char *str);
int in_array(char* needle, const char** haystack, int size);

/* For CuTest */
void RunAllTests(void);

/* Struct definitions */
struct area {
  int heaviness;
  int light;      /*ellenberg scale*/
  int calcium;    /*ellenberg scale*/
  int nutrient;   /*ellenberg scale*/
  int moisture;   /*ellenberg scale*/
  int totalArea;  /*m^2*/
  int mfoArea;    /*m^2*/
};

enum mfoTypes {
  mfoBraemmer,
  mfoBrak,
  mfoBestoeverbrak
};

enum red_list_categories {
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
  char danishName[MAX_NAME_LENGTH];
  char latinName[MAX_NAME_LENGTH];
  int lifespan;        /*years*/
  int heaviness;
  int light;           /*ellenberg scale*/
  int calcium;         /*ellenberg scale*/
  int nutrient;        /*ellenberg scale*/
  int moisture;        /*ellenberg scale*/
  /*
  mfoTypes is boolean:
  mfoTypes[mfoBraemmer] is approved for MFO-braemmer
  mfoTypes[mfoBrak] is approved for MFO-Brak
  mfoTypes[mfoBestoeverbrak] is approved for MFO-Bestoeverbrak
  */
  int mfoTypes[3];
};

struct matched_flora {
  char floraLatinName[MAX_NAME_LENGTH];
  char matchedFaunaLatinName[MAX_FLORA_PER_FAUNA][MAX_NAME_LENGTH];
};

struct fauna {
  char danishName[MAX_NAME_LENGTH];
  char latinName[MAX_NAME_LENGTH];
  enum red_list_categories endangerlvl;
  char *plants[MAX_NUMBER_OF_MATCHES];

};

/*Global debug option*/
int DEBUG = 0;

/* Global flora and fauna struct arrays */
struct flora flora[HASH_ARRAY_SIZE];
struct fauna fauna[HASH_ARRAY_SIZE];

/* Custom header files */
#include "input.h"
#include "flora.h"
#include "fauna.h"
#include "output.h"
#include "CuTest.h"

/* Main */
int main(int argc, char const *argv[]) {
  /*2 if statements to check if the program was run with a --debug or --test option*/
  if (argc > 1 && strcmp(argv[1], "--debug") == 0){
    DEBUG = 1;
  }

  if (argc > 1 && strcmp(argv[1], "--test") == 0) {
    RunAllTests();
  } else {
    struct area area = read_input();
    struct matched_flora matched_flora[MAX_NUMBER_OF_MATCHES];

    flora_database_and_matching(area, matched_flora);
    fauna_database_and_matching(matched_flora);
    create_output(matched_flora, area);
  }

  return EXIT_SUCCESS;
}

/* Function to capitalise a string*/
void to_upper(char *capitalise) {
  int i = 0;
  while (capitalise[i] != '\0'){
      capitalise[i] = toupper(capitalise[i]);
      i++;
  }
}

/* Hash function djb2 taken from http://www.cse.yorku.ca/~oz/hash.html */
int hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  /* Hash is trimmed to the HASHTABLE_SIZE */
  hash %= HASH_ARRAY_SIZE;

  return hash;
}

/*test if a string is in a array of strings*/
int in_array(char* needle, const char** haystack, int size) {
  int i;

  for (i = 0; i < size; i++) {
    if (strcmp(haystack[i], needle) == 0) {
      return 1;
    }
  }

  return 0;
}


/* CuTests */
void TestStrToUpperAlpha(CuTest *tc) {
  char* input = strdup("hello world");
  char* expected = "HELLO WORLD";
  to_upper(input);
  CuAssertStrEquals(tc, expected, input);
}

void TestStrToUpperSpecialChars(CuTest *tc) {
  char* input = strdup("HeLoLo @@ ## test 1234");
  char* expected = "HELOLO @@ ## TEST 1234";
  to_upper(input);
  CuAssertStrEquals(tc, expected, input);
}

void TestStrEndangerName(CuTest *tc) {
  enum red_list_categories inputValue = RE;
  char* input = endanger_name(inputValue);
  char* expected = "RE";
  CuAssertStrEquals(tc, expected, input);
}

void TestIntAprovedForMFOBestoeverbrakTrueValid(CuTest *tc) {
  char* inputValue = strdup("KNAUTIA ARVENSIS");
  int input = is_approved_for_mfo_bestoeverbrak(inputValue);
  int expected = 1;
  CuAssertIntEquals(tc, expected, input);
}

void TestIntAprovedForMFOBestoeverbrakFalseInvalid(CuTest *tc) {
  char* inputValue = strdup("       ");
  int input = is_approved_for_mfo_bestoeverbrak(inputValue);
  int expected = 0;
  CuAssertIntEquals(tc, expected, input);
}

void TestIntAprovedForMFOBestoeverbrakFalseValid(CuTest *tc) {
  char* inputValue = strdup("CENTAUREA CYANUS");
  int input = is_approved_for_mfo_bestoeverbrak(inputValue);
  int expected = 1;
  CuAssertIntEquals(tc, expected, input);
}

void TestStrGetPlantFamilyName(CuTest *tc) {
  char* inputValue = strdup("Magnus Ditlev");
  char input[20];
  char *expected =  strdup("Magnus");
  get_plant_family_name(inputValue, input);
  CuAssertStrEquals(tc, expected, input);
}

/* is_approved_for_mfo_braemme_or_mfo_brak */
void TestIntApprovedForMFOBraemmeFalseValidInput(CuTest *tc) {
  int input = is_approved_for_mfo_braemme_or_mfo_brak(2);
  int expected =  0;
  CuAssertIntEquals(tc, expected, input);
}

void TestIntApprovedForMFOBraemmeTrueValidInput(CuTest *tc) {
  int input = is_approved_for_mfo_braemme_or_mfo_brak(1);
  int expected =  1;
  CuAssertIntEquals(tc, expected, input);
}

void TestIntApprovedForMFOBraemmeFalseInvalidInput(CuTest *tc) {
  int input = is_approved_for_mfo_braemme_or_mfo_brak(-1);
  int expected =  0;
  CuAssertIntEquals(tc, expected, input);
}

/* mfo_types_sum */
void TestIntMfoTypesSumFalseValidInput(CuTest *tc) {
  int inputArray[3] = {0,0,0};
  int input = mfo_types_sum(inputArray);
  int expected =  0;
  CuAssertIntEquals(tc, expected, input);
}

void TestIntMfoTypesSumTrueValidInput(CuTest *tc) {
  int inputArray[3] = {1,1,1};
  int input = mfo_types_sum(inputArray);
  int expected =  3;
  CuAssertIntEquals(tc, expected, input);
}

void TestIntIsMatchFloraTrueValid(CuTest *tc) {
  struct flora inputFlora = {"Hoer","Linum usitatissimum",3,2,8,6,6,5};
  struct area inputArea = {2,7,5,6,5,5,5};
  int input, expected = 1;
  input = is_match_flora(inputFlora, inputArea);
  CuAssertIntEquals(tc, expected, input);
}

void TestIntIsMatchFloraFalseValid(CuTest *tc) {
  struct flora inputFlora = {"Hoer","Linum usitatissimum",3,2,8,6,6,5};
  struct area inputArea = {2,1,1,1,1,5,5};
  int input, expected = 0;
  input = is_match_flora(inputFlora, inputArea);
  CuAssertIntEquals(tc, expected, input);
}

void TestIntIsMatchFloraFalseInvalid(CuTest *tc) {
  struct flora inputFlora = {"Hoer","Linum usitatissimum",3,-3,8,-2,6,5};
  struct area inputArea = {2,8,6,6,5,5,5};
  int input, expected = 0;
  input = is_match_flora(inputFlora, inputArea);
  CuAssertIntEquals(tc, expected, input);
}

CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestStrToUpperAlpha);
  SUITE_ADD_TEST(suite, TestStrToUpperSpecialChars);
  SUITE_ADD_TEST(suite, TestStrEndangerName);
  SUITE_ADD_TEST(suite, TestStrGetPlantFamilyName);

  /* is_approved_for_mfo_bestoeverbrak */
  SUITE_ADD_TEST(suite, TestIntAprovedForMFOBestoeverbrakFalseValid);
  SUITE_ADD_TEST(suite, TestIntAprovedForMFOBestoeverbrakFalseInvalid);
  SUITE_ADD_TEST(suite, TestIntAprovedForMFOBestoeverbrakTrueValid);

  /* is_approved_for_mfo_braemme_or_mfo_brak */
  SUITE_ADD_TEST(suite, TestIntApprovedForMFOBraemmeTrueValidInput);
  SUITE_ADD_TEST(suite, TestIntApprovedForMFOBraemmeFalseValidInput);
  SUITE_ADD_TEST(suite, TestIntApprovedForMFOBraemmeFalseInvalidInput);

  /* mfo_types_sum */
  SUITE_ADD_TEST(suite, TestIntMfoTypesSumTrueValidInput);
  SUITE_ADD_TEST(suite, TestIntMfoTypesSumFalseValidInput);

  /*is_match_flora*/
  SUITE_ADD_TEST(suite, TestIntIsMatchFloraTrueValid);
  SUITE_ADD_TEST(suite, TestIntIsMatchFloraFalseValid);
  SUITE_ADD_TEST(suite, TestIntIsMatchFloraFalseInvalid);

  return suite;
}
/* End CUTests */
