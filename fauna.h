#define FAUNA_DATABASE "fauna.csv"
#define HASH_ARRAY_SIZE 1000
#define STR_LENGTH 100

/*
Function declarations for accessing and modifying fauna database
*/
void printFaunaTest();


void read_fauna_database(struct fauna *fauna) {
    char line[STR_LENGTH];
    int hashName;
    char* latinName;
    struct fauna read_fauna;
    
    FILE *fauna_ptr = fopen("FAUNA_DATABASE", "r");
    
    if (fauna_ptr != NULL){
        
        /* We skip the first line, containing headers of the file */
        fgets(line, STR_LENGTH, fauna_ptr);
        
        while (fgets(line, STR_LENGTH, fauna_ptr) != NULL){
            sscanf(line, " %[^,] , %[^,] , %i ", read_fauna.danishName, read_fauna.latinName, &read_fauna.endangerlvl);
            
            latinName = read_fauna.latinName;
            hashName = hash(latinName);
            fauna[hashName] = read_fauna;
            
            printf("%s %s\n", read_fauna.danishName, read_fauna.latinName);
            
            
        }
    }
    
    else{
        printf("Error\n");
    }
        
}

void printFaunaTest() {
  printf("Flora header file working\n");
  int i;
  struct fauna fauna[HASH_ARRAY_SIZE];
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    fauna[i] = (struct fuana) {};
  }

  read_fauna_database(fauna);
  /*printFaunaArray(flora);*/
}

/*void printFaunaArray(struct flora *flora) {
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
*/
