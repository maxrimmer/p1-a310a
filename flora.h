#define FLORA_DATABASE "flora.csv"
#define FLORA_HASH_ARRAY_SIZE 1000
#define MAX_NUMBER_OF_MATCHES 100
#define LINE_STR_LEN 120
/*
Function declarations for accessing and modifying flora database
*/
int hash(char *str);
void flora_matching(struct flora *flora_array, struct area area, struct matched_flora *matched_flora);
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

      to_upper(readFlora.latinName);
        
      latinName = readFlora.latinName;
      hashName = hash(latinName);
      flora[hashName] = readFlora;

    }

  }
}

void flora_matching(struct flora *flora_array, struct area area, struct matched_flora *matched_flora){
  int a, count = 0;
  for(a = 0; a < FLORA_HASH_ARRAY_SIZE; a++){
    if(strcmp(flora_array[a].latinName, "") != 0){
      if(is_match_flora(flora_array[a], area)){
        strcpy(matched_flora[count].floraLatinName, flora_array[a].latinName);
        //strcpy(resultlist[count], flora_array[a].latinName);
        //printf("hey HEY");
        count++;
      }
    }
  }
}

int is_match_flora(struct flora flora, struct area area){
  if(!flora_matching_checking(area.heaviness, flora.heaviness) && flora.heaviness != -1)
    return 0;

  if(!flora_matching_checking(area.light, flora.light) && flora.light != -1)
    return 0;

  if(!flora_matching_checking(area.moistness, flora.moistness) && flora.moistness != -1)
    return 0;

  if(!flora_matching_checking(area.nutrient, flora.nutrient) && flora.nutrient != -1)
    return 0;

  if(!flora_matching_checking(area.pH, flora.pH) && flora.pH != -1)
    return 0;

  return 1;
}

int flora_matching_checking(int area_attribute, int flora_attribute){
  if((area_attribute - flora_attribute) <= 1 && (area_attribute - flora_attribute) >= -1){
    return 1;
  }
  return 0;
}

void printFloraTest(struct area area) {
  printf("Flora header file working\n");
  int i;
  struct matched_flora matched_flora[MAX_NUMBER_OF_MATCHES];
  /*char result[100][40];*/
  struct flora flora[FLORA_HASH_ARRAY_SIZE];
  for (i = 0; i < FLORA_HASH_ARRAY_SIZE; i++) {
    flora[i] = (struct flora) {"", "", 0, 0, 0, 0, 0, 0};
  }

  read_flora_database(flora);
  printFloraArray(flora);

  for(i = 0; i < MAX_NUMBER_OF_MATCHES; i++){
    matched_flora[i] = (struct matched_flora) {" "};
    /*strcpy(result[i], " ");*/
  }
    //result[i] = "";
  flora_matching(flora, area, matched_flora);
  for(i = 0; i < 100; i++){
    if((strcmp(matched_flora[i].floraLatinName, " ") != 0)){
      printf("%s\n", matched_flora[i].floraLatinName);
    }
    //printf("%s", result);
  }
}

void printFloraArray(struct flora *flora) {
  int i;

  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    if (strcmp(flora[i].latinName, "") != 0) {
      printf("%-40s | %-40s | %2d | %2d | %2d | %2d | %2d | %2d\n",
      flora[i].danishName, flora[i].latinName, flora[i].lifespan,
      flora[i].heaviness, flora[i].light,    flora[i].pH,
      flora[i].nutrient,  flora[i].moistness);
    }
  }
}
