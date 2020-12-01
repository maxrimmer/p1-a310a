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
  struct flora readFlora;

  FILE *flora_file;
  flora_file = fopen(FLORA_DATABASE, "r");


  if (flora_file != NULL) {

    /* We skip the first line, containing headers of the file */
    fgets(line, LINE_STR_LEN, flora_file);
    while (fgets(line, LINE_STR_LEN, flora_file) != NULL) {

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

void flora_matching(struct flora *flora_array, struct area area, char **resultlist){
  int a, count = 0;
  for(a = 0; a < FLORA_HASH_ARRAY_SIZE; a++){
    if(strcmp(flora_array[a].latinName, "") != 0){
      if(is_match_flora(flora_array[a], area)){
        resultlist[count] = flora_array->latinName;
        count++;
      }
    }
  }
}

int is_match_flora(struct flora flora_array, struct area area){
  int a = 1;

  if(flora_matching_checking(area.heaviness, flora_array->light))
    a = 0;

  if(flora_matching_checking(area.light, flora_array->light))
    a = 0;

  if(flora_matching_checking(area.moistness, flora_array.moistness))
    a = 0;

  if(flora_matching_checking(area.nutrient, flora_array.nutrient))
    a = 0;

  if(flora_matching_checking(area.pH, flora_array.pH))
    a = 0;

  return a;
}

int flora_matching_checking(int area, int flora_array){
  if((area - flora_array) > 1 && (area - flora_array) < -1){
    return 1;
  }
  return 0;
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
