//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "src/structures/list_lexeme.h"
#include "src/analyse_lexicale/analyse_lexicale.h"




int main () {
  //CREATION DE LIST CHAINEE
  Lexeme_t *list1 = new_lexeme();
  Lexeme_t *list2 = new_lexeme();
  Lexeme_t *list3 = new_lexeme();
  if (is_empty(list1)) printf("EMPTY list\n");

  //ANALYSE LEXICALE
  analyse_lexicale("tests/ass.s", list1);
  print_list(list1);

  analyse_lexicale("tests/miam.s", list2);
  print_list(list2);

  analyse_lexicale("tests/mult.s", list3);
  print_list(list3);

	return 0;
}
