//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "src/structures/list_lexeme.h"
#include "src/analyse_lexicale/analyse_lexicale.h"




int main () {
  //CREATION DE LIST CHAINEE
  Lexeme_t *list = new_lexeme();
  if (is_empty(list)) printf("EMPTY list\n");

  //ANALYSE LEXICALE
  analyse_lexicale("tests/ass.s", list);

  print_list(list);

	return 0;
}
