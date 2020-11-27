#define FLORA_DATABASE "flora.csv"
#define LINE_STR_LEN 120
/*
Function declarations for accessing and modifying flora database
*/

void read_flora_database(struct flora *flora) {
  FILE *flora_file;
  flora_file = fopen(FLORA_DATABASE, "r");

  if (flora_file != NULL) {
    char line[LINE_STR_LEN];

    /* We skip the first line, containing headers of the file */
    fgets(line, LINE_STR_LEN, flora_file);
    while (fgets(line, LINE_STR_LEN, flora_file) != NULL) {
      struct flora readFlora;

      sscanf(line, " %[^,] , %[^,] ,%d,%d,%d,%d,%d,%d",
      readFlora.danishName, readFlora.latinName, &readFlora.lifespan,
      &readFlora.heaviness, &readFlora.light,    &readFlora.pH,
      &readFlora.nutrient,  &readFlora.moistness);

      printf("%-40s | %-40s | %2d | %2d | %2d | %2d | %2d | %2d\n",
      readFlora.danishName, readFlora.latinName, readFlora.lifespan,
      readFlora.heaviness, readFlora.light,    readFlora.pH,
      readFlora.nutrient,  readFlora.moistness);
    }

  }
}

void printFloraTest() {
  printf("Flora header file working\n");

  struct flora *flora;

  read_flora_database(flora);
}
