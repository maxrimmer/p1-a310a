#define FLORA_DATABASE "flora.csv"
#define FLORA_HASH_ARRAY_SIZE 1000
#define LINE_STR_LEN 120
/*
Function declarations for accessing and modifying flora database
*/
int hash(char *str);
void flora_matching(struct flora *flora_array, struct area area, char **resultlist);
int is_match_flora(struct flora flora_array, struct area area);
int flora_matching_checking(int area, int flora_array);
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
    printf("%d", a);
    if(strcmp(flora_array[a].latinName, "") != 0){
      printf("%s\n", flora_array[a].latinName);
      if(is_match_flora(flora_array[a], area)){
        printf("hey BEFORE");
        // printf("%s\n", flora_array[a].latinName);
        //strcpy(resultlist[count], flora_array[a].latinName);
        //printf("hey HEY");
        count++;
      }
    }
  }
}

int is_match_flora(struct flora flora_array, struct area area){

  if(!flora_matching_checking(area.heaviness, flora_array.heaviness))
    return 0;

  if(!flora_matching_checking(area.light, flora_array.light))
    return 0;

  if(!flora_matching_checking(area.moistness, flora_array.moistness))
    return 0;

  if(!flora_matching_checking(area.nutrient, flora_array.nutrient))
    return 0;

  if(!flora_matching_checking(area.pH, flora_array.pH))
    return 0;

  return 1;
}

int flora_matching_checking(int area, int flora_array){
  if((area - flora_array) <= 1 && (area - flora_array) <= -1){
    return 1;
  }
  return 0;
}

void printFloraTest(struct area area) {
  printf("Flora header file working\n");
  int i;
  char **result;
  struct flora flora[FLORA_HASH_ARRAY_SIZE];
  for (i = 0; i < FLORA_HASH_ARRAY_SIZE; i++) {
    flora[i] = (struct flora) {"", "", 0, 0, 0, 0, 0, 0};
  }

  read_flora_database(flora);
  printFloraArray(flora);

  result = (char**)malloc(100*40*sizeof(char));
  for(i = 0; i < 100; i++){
    strcpy(result[i], "");
  }
    //result[i] = "";
  flora_matching(flora, area, result);
  //for(i = 0; i < 100; i++){
    //printf("%s\n", result[i]);
    //printf("%s", result);
  //}
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
