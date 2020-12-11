#define FAUNA_DATABASE "fauna.csv"
#define FAUNA_PLANTS_ARRAY_SIZE 100
#define STR_LENGTH 200

/*
Function declarations for accessing and modifying fauna database
*/
void fauna_database_and_matching(struct flora *flora, struct matched_flora *matched_flora, struct fauna *fauna);
void read_fauna_database(struct fauna *fauna);
void printFaunaArray(struct fauna *fauna);
char *endanger_name (enum red_list_categories endangerlvl);
void read_plants (struct fauna *fauna, char *line);
void fauna_matching (struct fauna *fauna, struct flora *flora, struct matched_flora *matched_flora);
struct matched_flora add_fauna_to_matched_flora(char* faunaLatinName, struct matched_flora matched_flora);
void get_plant_family_name (const char* latinName, char familyName[40]);
void print_matched_flora(struct matched_flora *matched_flora);


void fauna_database_and_matching(struct flora *flora, struct matched_flora *matched_flora, struct fauna *fauna) {
  int i, j;

  /* Empties fauna array */
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    fauna[i] = (struct fauna) {"", "", 0};
  }

  read_fauna_database(fauna);
  printf("\n\nFauna database:\n");
  printFaunaArray(fauna);

  fauna_matching(fauna, flora, matched_flora);
  printf("\nMatched flora and fauna:\n");
  print_matched_flora(matched_flora);

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

void fauna_matching (struct fauna *fauna, struct flora *flora, struct matched_flora *matched_flora) {
  int i, j, k;
  char plantFamilyName[40];

  /* Set matched_flora.fauna to all empty strings */
  for (i = 0; i < MAX_NUMBER_OF_MATCHES; i++) {
    for (j = 0; j < 10; j++) {
      strcpy(matched_flora[i].matchedFaunaLatinName[j], "");
    }
  }

  /* Foreach fauna */
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    if (strcmp(fauna[i].latinName, "") != 0) {
      /* Foreach flora in fauna */
      j = 0;
      while (strcmp(fauna[i].plants[j], "") != 0) {

        /* Foreach matched_flora */
        k = 0;
        while (strcmp(matched_flora[k].floraLatinName, "") != 0 && k < MAX_NUMBER_OF_MATCHES) {
          get_plant_family_name(matched_flora[k].floraLatinName, plantFamilyName);
          /* If match between matched_flora.floraLatinName and fauna.plants[j] */
          if (strcmp(matched_flora[k].floraLatinName, fauna[i].plants[j]) == 0) {
            /* Add fauna.latinName[j] to matched_flora.matchedFaunaLatinName */
            matched_flora[k] = add_fauna_to_matched_flora(fauna[i].latinName, matched_flora[k]);
          }
          /* Else if match between get_plant_family_name(matched_flora.floraLatinName) and fauna.plants[j] */
          else if (strcmp(plantFamilyName, fauna[i].plants[j]) == 0) {
            /* Add fauna.latinName[j] to matched_flora.matchedFaunaLatinName */
            matched_flora[k] = add_fauna_to_matched_flora(fauna[i].latinName, matched_flora[k]);
          }
          k++;
        }
        j++;
      }
    }
  }
}

struct matched_flora add_fauna_to_matched_flora(char* faunaLatinName, struct matched_flora matched_flora) {
  int i = 0;
  while (i <= 10 && (strcmp(matched_flora.matchedFaunaLatinName[i], "") != 0)) {
    i++;
  }

  if (i == 10) {
    printf("Error: matched_flora out of memorry for fauna \n");
    exit(EXIT_FAILURE);
  }

  strcpy(matched_flora.matchedFaunaLatinName[i], faunaLatinName);

  return matched_flora;

}

void get_plant_family_name (const char* latinName, char* familyName) {
  int i, split;
  int size = strlen(latinName);

  split = size;
  for (i = 0; i < size; i++) {
    int result = (latinName[i] == ' ');
    if (result) {
      split = i;
      break;
    }
  }

  strncpy(familyName, latinName, split);
  familyName[split] = '\0';

}

void print_matched_flora(struct matched_flora *matched_flora) {
  int i;
  for (i = 0; i < MAX_NUMBER_OF_MATCHES; i++) {
    if (strcmp(matched_flora[i].floraLatinName, "") != 0) {
      printf("%-40s", matched_flora[i].floraLatinName);
      int j = 0;
      while (strcmp(matched_flora[i].matchedFaunaLatinName[j], "") != 0 && j < 10) {
        printf(" | %-40s", matched_flora[i].matchedFaunaLatinName[j]);
        j++;
      }
      printf("\n");
    }
  }
}
