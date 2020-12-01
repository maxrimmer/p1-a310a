#define FAUNA_DATABASE "fauna.csv"
#define HASH_ARRAY_SIZE 1000
#define STR_LENGTH 100

/*
Function declarations for accessing and modifying fauna database
*/
void printFaunaTest();
void read_fauna_database(struct fauna *fauna);
void printFaunaArray(struct fauna *fauna);
char *endanger_name (enum roedliste endangerlvl);


void printFaunaTest() {
  printf("Fauna header file working\n");
  int i;
  struct fauna fauna[HASH_ARRAY_SIZE];
  struct flora flora[HASH_ARRAY_SIZE];
    
  /* Empties fauna array */
  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    fauna[i] = (struct fauna) {"", "", 0, flora};
  }

  read_fauna_database(fauna);
  printFaunaArray(fauna);
}

void read_fauna_database(struct fauna *fauna) {
    char line[STR_LENGTH];
    int hashName;
    char* latinName;
    struct fauna read_fauna;
    int roed_danger;
    
    FILE *fauna_ptr = fopen(FAUNA_DATABASE, "r");
    
    if (fauna_ptr != NULL){
        
        /* We skip the first line, containing headers of the file */
        fgets(line, STR_LENGTH, fauna_ptr);
        
        while (fgets(line, STR_LENGTH, fauna_ptr) != NULL){
            sscanf(line, " %[^,] , %[^,] , %i ", read_fauna.danishName, read_fauna.latinName, &roed_danger);
            
            read_fauna.endangerlvl = (enum roedliste)roed_danger;
            
            latinName = read_fauna.latinName;
            hashName = hash(latinName);
            fauna[hashName] = read_fauna;
        }
    }
    
    else{
        printf("Error! Can't open file\n");
    }
        
}

void printFaunaArray(struct fauna *fauna) {
  int i;

  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    if (strcmp(fauna[i].latinName, "") != 0) {
      printf("%-40s | %-40s | %2s | nytteplante 1 | nytteplante 2 |\n",
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
