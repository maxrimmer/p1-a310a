#define HA_TO_M2_CONVERSIONRATIO 10000
/*This function returns ture if the input is between the upper and lower boundry*/
int inputVarification(int input, int lower_boundry, int upper_boundry);
int ha_to_m2_converter(float ha);
void error_40(int *checker);

struct area read_input(void) {
  struct area area;
  float ha;
  int checker = 0;
  printf("Velkommen til MFO forslag.\n"
  "Dette program vil ud fra dine indtastede oplysninger om dit areal\n"
  "foreslaa mulige planter der kan udplantes i arealet samt roedlistede\n"
  "arter der ville have gavn af disse planter\n");

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast dit omdriftsareals stoerrelse i ha. (decimaltal):\n");
    scanf(" %f", &ha);
  } while(ha <= 0.0);
  area.totalArea = ha_to_m2_converter(ha);
  checker = 0;

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast omraadet du oensker omlagt til MFO's stoerrelse i ha. (decimaltal):\n");
    scanf(" %f", &ha);
  } while(ha <= 0.0);
  area.mfoArea = ha_to_m2_converter(ha);
  checker = 0;

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast MFO arealets jords tunghed. (1-10, heltal):\n");
    scanf(" %d", &area.heaviness);
  } while(!inputVarification(area.heaviness, 1, 10));
  checker = 0;

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast MFO arealets jords lysforhold. (1-10, heltal):\n");
    scanf(" %d", &area.light);
  } while(!inputVarification(area.light, 1, 10));
  checker = 0;

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast MFO arealets jords pH-vaerdi. (0-14, heltal):\n");
    scanf(" %d", &area.pH);
  } while(!inputVarification(area.pH, 0, 14));
  checker = 0;

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast MFO arealets jords naeringsstofsindhold. (1-10, heltal):\n");
    scanf(" %d", &area.nutrient);
  } while(!inputVarification(area.nutrient, 1, 10));
  checker = 0;

  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast MFO arealets jords fugtighed. (1-10, heltal):\n");
    scanf(" %d", &area.moistness);
  } while(!inputVarification(area.moistness, 1, 10));
  checker = 0;

  return area;
}

int inputVarification(int input, int lower_boundry, int upper_boundry){
  return lower_boundry < input && input < upper_boundry;
}

int ha_to_m2_converter(float ha){
  return ha * HA_TO_M2_CONVERSIONRATIO;
}

void error_40(int *checker){
  if(*checker >= 1){
    printf("\ndet givende indput er ikke inden for det ønsket intervald", *checker);
    printf("\a");
  }
  *checker += 1;
}

int get_input (int ellenberg_value, ){
  int checker = 0;
  float return_this;
  do {
    fflush(stdin);
    error_40(&checker);
    printf("\nIndtast dit omdriftsareals stoerrelse i ha. (decimaltal):\n");
    scanf(" %f", &return_this);
  } while(return_this <= 0.0);

  if (ellenberg_value == 0)
    return_this = ha_to_m2_converter(return_this);

return (int) return_this;
}
