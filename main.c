//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "src/structures/list_lexeme.h"
#include "src/structures/list_etiquette.h"
#include "src/analyse_lexicale/analyse_lexicale.h"
#include "src/analyse_gramatical/etiquette.h"




int main () {
  //CREATION DE LIST CHAINEE
  Lexeme_t *list1 = new_lexeme();
  Lexeme_t *list2 = new_lexeme();
  Lexeme_t *list3 = new_lexeme();
  Etiquette_t *etiq1 = new_etiquette();
  Etiquette_t *etiq2 = new_etiquette();
  Etiquette_t *etiq3 = new_etiquette();

  if (is_empty(list1)) printf("EMPTY list\n");

  //ANALYSE LEXICALE
  analyse_lexicale("tests/ass.s", list1);
  //print_list(list1);

  analyse_lexicale("tests/miam.s", list2);
  //print_list(list2);

  analyse_lexicale("tests/mult.s", list3);
  //print_list(list3);

  cherche_etiquette(list1, etiq1);
  cherche_etiquette(list2, etiq2);
  cherche_etiquette(list3, etiq3);

  return 0;
}
