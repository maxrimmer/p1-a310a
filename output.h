#define OUTPUT_FILE_NAME "fundne_planter.txt"

/*
for printing results to .txt file
*/

/* Prototypes */
void create_output(struct matched_flora *matched_flora, struct flora *flora, struct fauna *fauna);
void print_mfo_types(int mfoTypes[3], FILE * output_file);


void create_output(struct matched_flora *matched_flora, struct flora *flora, struct fauna *fauna) {
  int i;
  FILE * output_file;
  output_file = fopen (OUTPUT_FILE_NAME, "w+");

  printf("%-40s | %-54s | %s\n", "Plantens navn", "MFO-omraader planten er godkendt til", "Insekter planten gavner");
  fprintf(output_file, "%-40s | %-54s | %s\n", "Plantens navn", "MFO-omraader planten er godkendt til", "Insekter planten gavner");

  for (i = 0; i < MAX_NUMBER_OF_MATCHES; i++) {
    if (strcmp(matched_flora[i].floraLatinName, "") != 0) {
      int floraHash = hash(matched_flora[i].floraLatinName);
      printf("%-40s |", flora[floraHash].danishName);
      fprintf(output_file, "%-40s |", flora[floraHash].danishName);

      print_mfo_types(flora[floraHash].mfoTypes, output_file);

      int j = 0;
      while (strcmp(matched_flora[i].matchedFaunaLatinName[j], "") != 0 && j < 10) {
        int faunaHash = hash(matched_flora[i].matchedFaunaLatinName[j]);
        if (j == 0) {
            printf(" %s (%s)", fauna[faunaHash].danishName, endanger_name(fauna[faunaHash].endangerlvl));
            fprintf(output_file, " %s (%s)", fauna[faunaHash].danishName, endanger_name(fauna[faunaHash].endangerlvl));
        } else {
            printf(", %s (%s)", fauna[faunaHash].danishName, endanger_name(fauna[faunaHash].endangerlvl));
            fprintf(output_file, ", %s (%s)", fauna[faunaHash].danishName, endanger_name(fauna[faunaHash].endangerlvl));
        }
        j++;
      }
      printf("\n");
      fprintf(output_file, "\n");
    }
  }

  fclose(output_file);
}

void print_mfo_types(int mfoTypes[3], FILE * output_file) {
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
