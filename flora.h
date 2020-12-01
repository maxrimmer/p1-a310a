#define FLORA_DATABASE "flora.csv"
#define FLORA_HASH_ARRAY_SIZE 1000
#define LINE_STR_LEN 120
/*
Function declarations for accessing and modifying flora database
*/
int hash(char *str);
void printFloraArray(struct flora *flora);

void read_flora_database(struct flora *flora) {
  int hashName;
  char* latinName;
  char line[LINE_STR_LEN];

  FILE *flora_file;
  flora_file = fopen(FLORA_DATABASE, "r");


  if (flora_file != NULL) {

    /* We skip the first line, containing headers of the file */
    fgets(line, LINE_STR_LEN, flora_file);
    while (fgets(line, LINE_STR_LEN, flora_file) != NULL) {
      struct flora readFlora;

      sscanf(line, " %[^,] , %[^,] , %d , %d , %d , %d , %d , %d ",
      readFlora.danishName, readFlora.latinName, &readFlora.lifespan,
      &readFlora.heaviness, &readFlora.light,    &readFlora.pH,
      &readFlora.nutrient,  &readFlora.moistness);

      latinName = readFlora.latinName;
      hashName = hash(latinName);
      flora[hashName] = readFlora;

    }

  }
}

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

void printFloraTest() {
  printf("Flora header file working\n");
  int i;
  struct flora flora[FLORA_HASH_ARRAY_SIZE];
  for (i = 0; i < FLORA_HASH_ARRAY_SIZE; i++) {
    flora[i] = (struct flora) {"", "", 0, 0, 0, 0, 0, 0};
  }

  read_flora_database(flora);

  printFloraArray(flora);
}

void printFloraArray(struct flora *flora) {
  int i;

  for (i = 0; i < FLORA_HASH_ARRAY_SIZE; i++) {
    if (strcmp(flora[i].latinName, "") != 0) {
      printf("%-40s | %-40s | %2d | %2d | %2d | %2d | %2d | %2d\n",
      flora[i].danishName, flora[i].latinName, flora[i].lifespan,
      flora[i].heaviness, flora[i].light,    flora[i].pH,
      flora[i].nutrient,  flora[i].moistness);
    }
  }
}
