#define FAUNA_DATABASE "fauna.csv"
#define FAUNA_PLANTS_ARRAY_SIZE 100
#define HASH_ARRAY_SIZE 1000
#define STR_LENGTH 200

/*
Function declarations for accessing and modifying fauna database
*/
void printFaunaTest();
void read_fauna_database(struct fauna *fauna);
void printFaunaArray(struct fauna *fauna);
char *endanger_name (enum roedliste endangerlvl);
void to_upper (struct fauna *fauna);
void read_plants (struct fauna *fauna, char *line);


void printFaunaTest() {
  printf("Fauna header file working\n");
  int i;
  struct fauna fauna[HASH_ARRAY_SIZE];
  struct flora flora[HASH_ARRAY_SIZE];
    
  /* Empties fauna array */
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    fauna[i] = (struct fauna) {"", "", 0};
  }

  read_fauna_database(fauna);
  printFaunaArray(fauna);
}

void read_fauna_database(struct fauna *fauna) {
    char line[STR_LENGTH];
    int hashName;
    char* latinName;
    struct fauna read_fauna;
    int roed_danger, i, j;
    
    FILE *fauna_ptr = fopen(FAUNA_DATABASE, "r");
    
    if (fauna_ptr != NULL){
        /* We skip the first line, containing headers of the file */
        fgets(line, STR_LENGTH, fauna_ptr);
        
        while (fgets(line, STR_LENGTH, fauna_ptr) != NULL){
            sscanf(line, " %[^,] , %[^,] , %i ", read_fauna.danishName, read_fauna.latinName, &roed_danger);
            
            read_fauna.endangerlvl = (enum roedliste)roed_danger;
            for(i = 0; i < FAUNA_PLANTS_ARRAY_SIZE; i++){
                if((read_fauna.plants[i] = (char *)malloc(40*sizeof(char))) == NULL){
                    printf("Malloc fail");
                    exit(EXIT_FAILURE);
                }
                strcpy(read_fauna.plants[i], ""); 
            }
            read_plants(&read_fauna, line);
            to_upper(&read_fauna);
            
            latinName = read_fauna.latinName;
            hashName = hash(latinName);
            fauna[hashName] = read_fauna;
        }
        for (i = 0; i < HASH_ARRAY_SIZE; i++){
            if (strcmp(fauna[i].danishName, "") != 0){
                for(j = 0; j < FAUNA_PLANTS_ARRAY_SIZE; j++){
                    free(fauna[i].plants[j]);
                }
            }
        }
    }
    else{
        printf("Error! Can't open file\n");
    }
}

void read_plants(struct fauna *fauna, char *line){
    int start_point = (int)strlen(fauna->danishName) + (int)strlen(fauna->latinName) + 4;
    int i = 0;
    int j = start_point;
    /*runs until there are no more names on the line*/
    while (line[j] != '\0'){
        /*runs until the plant's name has been found*/
        while (line[j] != ',' && line[j] != '\0' && line[j] != '\n' && j < STR_LENGTH){
            fauna->plants[i][j - start_point] = line[j];
            j++;
        }
        fauna->plants[i][j] = '\0';
        if(strcmp(fauna->plants[i], "") != 0)
            printf("%s\n", fauna->plants[i]);
        j++;
        start_point = j;
        i++;
    }
}
/* Function to capitalise latin name */
void to_upper(struct fauna *fauna){
    int i = 0;
    while (fauna->latinName[i] != '\0'){
        fauna->latinName[i] = toupper(fauna->latinName[i]);
        i++;
    }
}

void printFaunaArray(struct fauna *fauna) {
  int i;

  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    if (strcmp(fauna[i].latinName, "") != 0) {
      printf("%-40s | %-40s | %2s | nyt | nyt |\n",
      fauna[i].danishName, fauna[i].latinName, endanger_name(fauna[i].endangerlvl));
    }
  }
}

char *endanger_name (enum roedliste endangerlvl){
    switch (endangerlvl) {
        case RE:
            return "RE";
        case CR:
            return "CR";
        case EN:
            return "EN";
        case VU:
            return "VU";
        case NT:
            return "NT";
        case DD:
            return "DD";
        case LC:
            return "LC";
        case NA:
            return "NA";
        case NE:
            return "NE";
        default:
            return "Error";
    }
}
