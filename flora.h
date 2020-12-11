#define FLORA_DATABASE "flora.csv"
#define FLORA_HASH_ARRAY_SIZE 1000
#define LINE_STR_LEN 120
/*
Function declarations for accessing and modifying flora database
*/
void flora_database_and_matching(struct area area, struct flora *flora, struct matched_flora *matched_flora);
void read_flora_database(struct flora *flora);
void add_mfo_to_flora(struct flora *flora);
int is_approved_for_mfo_braemme_or_mfo_brak (int lifespan);
int is_approved_for_mfo_bestoeverbrak (char* latinName);
void flora_matching(struct flora *flora_array, struct area area, struct matched_flora *matched_flora);
int is_match_flora(struct flora flora_array, struct area area);
int flora_matching_checking(int area, int flora_array);
void print_flora_array(struct flora *flora);

/* Function for handling all of the flora block */
void flora_database_and_matching(struct area area, struct flora *flora, struct matched_flora *matched_flora) {
  printf("Flora header file working\n");
  int i;
  for (i = 0; i < FLORA_HASH_ARRAY_SIZE; i++) {
    flora[i] = (struct flora) {"", "", 0, 0, 0, 0, 0, 0};
  }

  read_flora_database(flora);
  add_mfo_to_flora(flora);
  print_flora_array(flora);

  for(i = 0; i < MAX_NUMBER_OF_MATCHES; i++){
    matched_flora[i] = (struct matched_flora) {""};
  }

  flora_matching(flora, area, matched_flora);
}

void read_flora_database(struct flora *flora) {
  int hashName;
  char* latinName;
  char line[LINE_STR_LEN];
  struct flora readFlora;

  FILE *flora_file;
  flora_file = fopen(FLORA_DATABASE, "r");


  if (flora_file != NULL) {

    /* We validate the first line, containing headers of the file */
    fgets(line, LINE_STR_LEN, flora_file);
    if(!(strncmp(line, "Dansk navn,Latinsk navn,Levetid (aar),Tunghed(1-10),Lystal (L),Calciumtal (R),Kvaelstof (N),Fugtighedstal (F)", 109)) == 0) {
      printf("Headers in flora csv file incorrect!\n");
      exit(EXIT_FAILURE);
    }
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

/* Function for adding MFO data to the flora struct */
void add_mfo_to_flora (struct flora *flora) {
  int i;

  for (i = 0; i < FLORA_HASH_ARRAY_SIZE; i++) {
    if(strcmp(flora[i].latinName, "") != 0){
      flora[i].mfoTypes[mfoBraemmer] = 0;
      flora[i].mfoTypes[mfoBrak] = 0;
      flora[i].mfoTypes[mfoBestoeverbrak] = 0;

      if (is_approved_for_mfo_braemme_or_mfo_brak(flora[i].lifespan)) {
        flora[i].mfoTypes[mfoBraemmer] = 1;
        flora[i].mfoTypes[mfoBrak] = 1;
      }

      if (is_approved_for_mfo_bestoeverbrak(flora[i].latinName)) {
        flora[i].mfoTypes[mfoBraemmer] = 1;
        flora[i].mfoTypes[mfoBrak] = 1;
        flora[i].mfoTypes[mfoBestoeverbrak] = 1;
      }

    }
  }
}

int is_approved_for_mfo_braemme_or_mfo_brak (int lifespan) {
  if (lifespan == 1) {
    return 1;
  }

  return 0;
}

int is_approved_for_mfo_bestoeverbrak (char* latinName) {
  const char* approved_flora[] = {
    "KNAUTIA ARVENSIS",
    "GLEBIONIS SEGETUM",
    "LEUCANTHEMUM VULGARE",
    "SINAPIS ALBA",
    "BORAGO OFFICINALIS",
    "PHACELIA TANACETIFOLIA",
    "CALENDULA OFFICINALIS",
    "LINUM USITATISSIMUM",
    "ANTHYLLIS VULNERARIA",
    "FAGOPYRUM ESCULENTUM",
    "CICHORIUM INTYBUS",
    "CENTAUREA CYANUS",
    "PAPAVER RHOEAS",
    "DAUCUS CAROTA",
    "ACHILLEA MILLIFOLIA",
    "CARUM CARVI",
    "ANTHRISCUS SYLVESTRIS",
    "PRUNELLA VULGARIS",
    "LOTUS COMICULATUM",
    "TRIFOLIUM PRATENSE",
    "TRIFOLIUM HYBRIDUM",
    "TRIFOLIUM INCARNATUM",
    "TRIFOLIUM REPENS",
    "MEDICAGO SATIVA",
    "MELILOTUS OFFICINALIS",
    "VICIA CRACCA",
    "ONOBRYCHIS VICIIFOLIA",
    "MEDICAGO LUPULINA"
  };

  int approved_flora_size = (sizeof(approved_flora) / sizeof(const char *));
  return in_array(latinName, approved_flora, approved_flora_size);

}

void flora_matching (struct flora *flora_array, struct area area, struct matched_flora *matched_flora){
  int a, count = 0;
  for(a = 0; a < FLORA_HASH_ARRAY_SIZE; a++){
    if(strcmp(flora_array[a].latinName, "") != 0){
      if(is_match_flora(flora_array[a], area)){
        strcpy(matched_flora[count].floraLatinName, flora_array[a].latinName);
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

void print_flora_array(struct flora *flora) {
  int i;

  for (i = 0; i < HASH_ARRAY_SIZE; i++) {
    if (strcmp(flora[i].latinName, "") != 0) {
      printf("%-40s | %-40s | %2d | %2d | %2d | %2d | %2d | %2d",
      flora[i].danishName, flora[i].latinName, flora[i].lifespan,
      flora[i].heaviness, flora[i].light,    flora[i].pH,
      flora[i].nutrient,  flora[i].moistness);

      if (flora[i].mfoTypes[mfoBraemmer]) {
        printf(" | Godkendt til MFO-braemmer");
      }
      if (flora[i].mfoTypes[mfoBrak]) {
        printf(" | Godkendt til MFO-brak");
      }
      if (flora[i].mfoTypes[mfoBestoeverbrak]) {
        printf(" | Godkendt til MFO-blomster- og bestoeverbrak");
      }
      printf("\n");
    }
  }
}
