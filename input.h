#define HA_TO_M2_CONVERSIONRATIO 10000
/*This function returns ture if the input is between the upper and lower boundry*/
int inputVerification(int input, int lower_boundry, int upper_boundry);
int ha_to_m2_converter(float ha);
void error_40(int *checker);
int get_input(int is_ellenberg_value, int lower_boundry, int upper_boundry);
int ellenberg_value_condition (int input, int is_ellenburg_value, int lower_boundry, int upper_boundry);

struct area read_input(void) {
  struct area area;
  printf("Velkommen til MFO forslag.\n"
  "Dette program vil ud fra dine indtastede oplysninger om dit areal\n"
  "foreslaa mulige planter der kan udplantes i arealet samt roedlistede\n"
  "arter der ville have gavn af disse planter\n");

  printf("\nIndtast dit omdriftsareals stoerrelse i ha. (decimaltal):\n");
  area.totalArea = get_input(0, 0, 0);

  printf("\nIndtast omraadet du oensker omlagt til MFO's stoerrelse i ha. (decimaltal):\n");
  area.mfoArea = get_input(0, 0, 0);

  printf("\nIndtast MFO arealets jords tunghed. (1-10, heltal):\n");
  area.heaviness = get_input(1, 1, 10);

  printf("\nIndtast MFO arealets jords lysforhold. (1-10, heltal):\n");
  area.light = get_input(1, 1, 10);

  printf("\nIndtast MFO arealets jords pH-vaerdi. (0-14, heltal):\n");
  area.pH = get_input(1, 1, 14);

  printf("\nIndtast MFO arealets jords naeringsstofsindhold. (1-10, heltal):\n");
  area.nutrient = get_input(1, 1, 10);

  printf("\nIndtast MFO arealets jords fugtighed. (1-10, heltal):\n");
  area.moistness = get_input(1, 1, 10);

  return area;
}

int inputVerification(int input, int lower_boundry, int upper_boundry){
  return lower_boundry <= input && input <= upper_boundry;
}

int ha_to_m2_converter(float ha){
  return ha * HA_TO_M2_CONVERSIONRATIO;
}

int get_input(int is_ellenberg_value, int lower_boundry, int upper_boundry){
  int checker = 0;
  float input;
  do {
    fflush(stdin);
    error_40(&checker);
    scanf(" %f", &input);
  } while(ellenberg_value_condition(input, is_ellenberg_value, lower_boundry, upper_boundry));

  if (is_ellenberg_value == 0)
    input = ha_to_m2_converter(input);

  return (int) input;
}

void error_40(int *checker){
  if(*checker >= 1){
    printf("Den indtastede vaerdi er ikke inden for det paakraevede interval.\n");
    printf("\a");
  }
  *checker += 1;
}

int ellenberg_value_condition (int input, int is_ellenburg_value, int lower_boundry, int upper_boundry){
  if(is_ellenburg_value == 1){
    return !inputVerification(input, lower_boundry, upper_boundry);
  }
  return input <= 0.0;
}