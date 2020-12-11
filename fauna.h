#define FAUNA_DATABASE "fauna.csv"
#define FAUNA_PLANTS_ARRAY_SIZE 100
#define HASH_ARRAY_SIZE 1000
#define STR_LENGTH 200

/*
Function declarations for accessing and modifying fauna database
*/
void fauna_database_and_matching(struct matched_flora *matched_flora);
void read_fauna_database(struct fauna *fauna);
void printFaunaArray(struct fauna *fauna);
char *endanger_name (enum red_list_categories endangerlvl);
void read_plants (struct fauna *fauna, char *line);


void fauna_database_and_matching(struct matched_flora *matched_flora) {
  int i, j;
  struct fauna fauna[HASH_ARRAY_SIZE];
  struct flora flora[HASH_ARRAY_SIZE];
  printf("Fauna header file working\n");

  /* Empties fauna array */
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    fauna[i] = (struct fauna) {"", "", 0};
  }
  
  read_fauna_database(fauna);
  printFaunaArray(fauna);
  
  for (i = 0; i < HASH_ARRAY_SIZE; i++){
        if (strcmp(fauna[i].danishName, "") != 0){
            for(j = 0; j < FAUNA_PLANTS_ARRAY_SIZE; j++){
                free(fauna[i].plants[j]);
            }
        }
    }
}

void read_fauna_database(struct fauna *fauna) {
    char line[STR_LENGTH];
    int hashName;
    char* latinName;
    struct fauna read_fauna;
    int danger_category, i;

    FILE *fauna_ptr = fopen(FAUNA_DATABASE, "r");

    if (fauna_ptr != NULL){
        /* We validate the first line, containing headers of the file */
        fgets(line, STR_LENGTH, fauna_ptr);
        if(!(strncmp(line, "Dansk navn,Latinsk navn,Truet,Nytteplante 1,Nytteplante 2,Nytteplante 3,Nytteplante 4,Nytteplante 5,Nytteplante 6", 113)) == 0) {
            printf("Headers in fauna csv file incorrect!\n");
            exit(EXIT_FAILURE);
        }

        while (fgets(line, STR_LENGTH, fauna_ptr) != NULL){
            sscanf(line, " %[^,] , %[^,] , %i ", read_fauna.danishName, read_fauna.latinName, &danger_category);

            read_fauna.endangerlvl = (enum red_list_categories)danger_category;

            for(i = 0; i < FAUNA_PLANTS_ARRAY_SIZE; i++){
                if((read_fauna.plants[i] = (char *)malloc(40*sizeof(char))) == NULL){
                    printf("Malloc fail");
                    exit(EXIT_FAILURE);
                }
                strcpy(read_fauna.plants[i], "");
            }

            read_plants(&read_fauna, line);
            to_upper(read_fauna.latinName);

            latinName = read_fauna.latinName;
            hashName = hash(latinName);
            fauna[hashName] = read_fauna;
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
            /*special case to fix a very wierd bug*/
            if(strcmp(fauna->danishName, "Murergnavebi") == 0)
                fauna->plants[i][j - start_point + 14] = '\0';
            fauna->plants[i][j - start_point] = line[j];
            j++;
        }
        fauna->plants[i][j] = '\0';
        to_upper(fauna->plants[i]);
        j++;
        start_point = j;
        i++;
    }
}


void printFaunaArray(struct fauna *fauna) {
  int i, j = 0;
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    if (strcmp(fauna[i].latinName, "") != 0) {
      printf("%-40s | %-40s | %2s |",
      fauna[i].danishName, fauna[i].latinName, endanger_name(fauna[i].endangerlvl));
        while (strcmp(fauna[i].plants[j], "") != 0){
          printf(" %-20s |", fauna[i].plants[j]);
          j++;
        }
        printf("\n");
        j = 0;
    }
  }
}

char *endanger_name (enum red_list_categories endangerlvl){
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
