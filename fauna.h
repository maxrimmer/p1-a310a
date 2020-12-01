#define FAUNA_DATABASE "fauna.csv"
#define STR_LENGTH 100

/*
Function declarations for accessing and modifying fauna database
*/

struct fauna read_fauna;

void printFaunaTest() {
    char line[STR_LENGTH];
    
    FILE *fauna_ptr = fopen("fauna.csv", "r");
    
    struct fauna *fauna_array = malloc (sizeof(struct fauna) * 18);
    
    if (fauna_ptr != NULL){
        
        fgets(line, STR_LENGTH, fauna_array);
        
        while (fgets(line, STR_LENGTH, fauna_array) != NULL){
            sscanf(line, " %[^,] , %[^,] , %i ", read_fauna.danishName, read_fauna.latinName, &read_fauna.endangerlvl);
            
            printf("%s\n", read_fauna.danishName);
            
            
        }
    }
    
    else{
        printf("Error\n");
    }
        
}
