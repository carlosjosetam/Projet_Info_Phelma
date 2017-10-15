#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "etiquette.c"

void analyse_gramatical_1(Lexeme_t * head_lexemes, Etiquette_t * list_etiquettes) {
  cherche_etiquette(head_lexemes, list_etiquettes);
}
