/*This function returns ture if the input is between the upper and lower boundry*/
int inputVarification(int input, int lower_boundry, int upper_boundry);

struct area read_input(void) {
  struct area area;
  printf("Velkommen til MFO forslag.\n"
  "Dette program vil ud fra dine indtastede oplysninger om dit areal\n"
  "foreslaa mulige planter der kan udplantes i arealet samt roedlistede\n"
  "arter der ville have gavn af disse planter\n\n");

  do {
    printf("Indtast venligst dit omdriftsareals stoerrelse i ha. (indtast som decimaltal):\n");
    scanf(" %lf", &area.totalArea);
  } while(area.totalArea <= 0.0);

  do {
    printf("Indtast venligst omraadet du oensker omlagt til MFO's stoerrelse i ha. (indtast som decimaltal):\n");
    scanf(" %lf", &area.mfoArea);
  } while(area.totalArea <= 0.0);

  do {
    printf("Indtast venligst MFO arealets jords tunghed. (1-10, heltal):\n");
    scanf(" %d", &area.heaviness);
  } while(!inputVarification(area.heaviness, 1, 10));

  do {
    printf("Indtast venligst MFO arealets jords lysforhold. (1-10, heltal):\n");
    scanf(" %d", &area.light);
  } while(!inputVarification(area.light, 1, 10));

  do {
    printf("Indtast venligst MFO arealets jords pH-vaerdi. (0-14, heltal):\n");
    scanf(" %d", &area.pH);
  } while(!inputVarification(area.pH, 0, 14));

  do {
    printf("Indtast venligst MFO arealets jords naeringsstofsindhold. (1-10, heltal):\n");
    scanf(" %d", &area.nutrient);
  } while(!inputVarification(area.nutrient, 1, 10));

  do {
    printf("Indtast venligst MFO arealets jords fugtighed. (1-10, heltal):\n");
    scanf(" %d", &area.moistness);
  } while(!inputVarification(area.moistness, 1, 10));

  return area;
}

int inputVarification(int input, int lower_boundry, int upper_boundry){
  return lower_boundry < input && input < upper_boundry;
}
