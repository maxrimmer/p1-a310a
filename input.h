#define HA_TO_M2_CONVERSIONRATIO 10000
/*This function returns ture if the input is between the upper and lower boundry*/
int inputVerification(int input, int lower_boundry, int upper_boundry);
int ha_to_m2_converter(float ha);
void error_if_input_is_outside_range(int *checker);
int get_input(int is_ellenberg_value, int lower_boundry, int upper_boundry);
int ellenberg_value_condition (int input, int is_ellenberg_value, int lower_boundry, int upper_boundry);

struct area read_input(void) {
  struct area area;
  printf("Velkommen til MFO forslag.\n"
  "Dette program vil ud fra dine indtastede oplysninger om dit areal   \n"
  "foreslaa mulige planter der kan udplantes i arealet samt roedlistede\n"
  "arter der ville have gavn af disse planter. Arealoplysningerne skal \n"
  "oplyses ud fra Ellenbergs indikatorvaerdier, information om disse   \n"
  "kan findes paa kortlink.dk/29ppc , undtagelsen er jordens tunghed   \n"
  "hvor 1 er sandjord, 9 er lerjord, og 5 er midt i mellem             \n");

  printf("\nIndtast dit omdriftsareals stoerrelse i ha. (decimaltal):\n");
  area.totalArea = get_input(0, 0, 0);

  printf("\nIndtast omraadet du oensker omlagt til MFO's stoerrelse i ha. (decimaltal):\n");
  area.mfoArea = get_input(0, 0, 0);

  printf("\nIndtast MFO arealets jords tunghed. (1-9, heltal):\n");
  area.heaviness = get_input(1, 1, 9);

  printf("\nIndtast MFO arealets jords lystal. (1-9, heltal):\n");
  area.light = get_input(1, 1, 9);

  printf("\nIndtast MFO arealets jords calciumtal. (1-9, heltal):\n");
  area.calcium = get_input(1, 1, 9);

  printf("\nIndtast MFO arealets jords kvaelstofstal. (1-9, heltal):\n");
  area.nutrient = get_input(1, 1, 9);

  printf("\nIndtast MFO arealets jords fugtighedstal. (1-12, heltal):\n");
  area.moisture = get_input(1, 1, 12);

  return area;
}
/*Bool function that verifies if the input is between the boundries*/
int inputVerification(int input, int lower_boundry, int upper_boundry) {
  return lower_boundry <= input && input <= upper_boundry;
}

int ha_to_m2_converter(float ha) {
  return ha * HA_TO_M2_CONVERSIONRATIO;
}

int get_input(int is_ellenberg_value, int lower_boundry, int upper_boundry) {
  int checker = 0;
  float input;
  do {
    fflush(stdin);
    error_if_input_is_outside_range(&checker);
    scanf(" %f", &input);
  } while(ellenberg_value_condition(input, is_ellenberg_value, lower_boundry, upper_boundry));
  /*if it isn't a ellenberg value, then it needs to be converted from ha to m2*/
  if (!is_ellenberg_value) {
    input = ha_to_m2_converter(input);
  }

  return (int) input;
}

void error_if_input_is_outside_range(int *checker) {
  if (*checker >= 1) {
    printf("Den indtastede vaerdi er ikke inden for det paakraevede interval.\n");
    printf("\a");
  }

  *checker += 1;
}

int ellenberg_value_condition(int input, int is_ellenberg_value, int lower_boundry, int upper_boundry) {
  if (is_ellenberg_value == 1) {
    return !inputVerification(input, lower_boundry, upper_boundry);
  }
  
  return input <= 0.0;
}
