#define OUTPUT_FILE_NAME "fundne_planter.txt"

/*
for printing results to .txt file
*/

/* Prototypes */
void create_output(struct matched_flora *matched_flora);
int compFunc (const void * a, const void * b);
int mfo_types_sum(int mfoTypes[3]);
float vulnerability_average(struct matched_flora *matched_flora);
void print_mfo_types(int mfoTypes[3], FILE *output_file);


void create_output(struct matched_flora *matched_flora) {
  int i, j;
  FILE *output_file;
  output_file = fopen (OUTPUT_FILE_NAME, "w+");

  printf("%-40s | %-54s | %s\n", "Plantens navn", "MFO-omraader planten er godkendt til", "Insekter planten gavner");
  fprintf(output_file, "%-40s | %-54s | %s\n", "Plantens navn", "MFO-omraader planten er godkendt til", "Insekter planten gavner");

  qsort(matched_flora, MAX_NUMBER_OF_MATCHES, sizeof(struct matched_flora), *compFunc);

  for (i = 0; i < MAX_NUMBER_OF_MATCHES; i++) {
    if (strcmp(matched_flora[i].floraLatinName, "") != 0) {
      int floraHash = hash(matched_flora[i].floraLatinName);
      printf("%-40s |", flora[floraHash].danishName);
      fprintf(output_file, "%-40s |", flora[floraHash].danishName);

      print_mfo_types(flora[floraHash].mfoTypes, output_file);

      j = 0;
      while (strcmp(matched_flora[i].matchedFaunaLatinName[j], "") != 0 && j < 10) {
        int faunaHash = hash(matched_flora[i].matchedFaunaLatinName[j]);
        if (j != 0) {
          printf(",");
          fprintf(output_file, ",");
        }
        printf(" %s (%s)", fauna[faunaHash].danishName, endanger_name(fauna[faunaHash].endangerlvl));
        fprintf(output_file, " %s (%s)", fauna[faunaHash].danishName, endanger_name(fauna[faunaHash].endangerlvl));
        j++;
      }
      printf("\n");
      fprintf(output_file, "\n");
    }
  }
  fclose(output_file);
}

/* Comparison function for qsort */
int compFunc (const void *a, const void *b) {
  struct matched_flora *matched_flora1 = (struct matched_flora *)a;
  struct matched_flora *matched_flora2 = (struct matched_flora *)b;

  int matched_flora1_hash, matched_flora2_hash;

  /* Empty ones go last */
  if (strcmp(matched_flora1->floraLatinName, "") == 0) {
    return 1;
  }
  if (strcmp(matched_flora2->floraLatinName, "") == 0) {
    return -1;
  }

  matched_flora1_hash = hash(matched_flora1->floraLatinName);
  matched_flora2_hash = hash(matched_flora2->floraLatinName);

  /* Most approved MFO types go first */
  if (mfo_types_sum(flora[matched_flora1_hash].mfoTypes) > mfo_types_sum(flora[matched_flora2_hash].mfoTypes)) {
    return -1;
  }
  if (mfo_types_sum(flora[matched_flora2_hash].mfoTypes) > mfo_types_sum(flora[matched_flora1_hash].mfoTypes)) {
    return 1;
  }

  /* Supporting the most vulnerable fauna goes first */
  if (vulnerability_average(matched_flora1) < vulnerability_average(matched_flora2)) {
    return -1;
  }
  if (vulnerability_average(matched_flora2) < vulnerability_average(matched_flora1)) {
    return 1;
  }

  /* All else equal */
  return 0;
}

int mfo_types_sum(int mfoTypes[3]) {
  int i, sum = 0;
  for (i = 0; i < 2; i++) {
    sum += mfoTypes[i];
  }

  return sum;
}

float vulnerability_average(struct matched_flora *matched_flora) {
  int i = 0, sum = 0;
  while (strcmp(matched_flora->matchedFaunaLatinName[i], "") != 0 && i < 10) {
    int faunaHash = hash(matched_flora->matchedFaunaLatinName[i]);
    sum += fauna[faunaHash].endangerlvl;
    i++;
  }
  /* Not helping any fauna */
  if (i == 0) {
    return 1000;
  }

/* Returning average, with bias for more fauna */
  return (float) sum/ (float) (i+1) - (i*0.5);
}

void print_mfo_types(int mfoTypes[3], FILE *output_file) {
  char* mfoPrint;
  if (mfoTypes[2]) {
    mfoPrint = "MFO-braemmer, MFO-brak, MFO-blomster- og bestoeverbrak";
  } else if (mfoTypes[1]) {
    mfoPrint = "MFO-braemmer, MFO-brak";
  } else {
    mfoPrint = "";
  }
  printf(" %-54s |", mfoPrint);
  fprintf(output_file, " %-54s |", mfoPrint);
}
