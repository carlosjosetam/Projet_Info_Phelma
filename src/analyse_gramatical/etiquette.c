#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structures/list_etiquette.h"
#include "../structures/list_etiquette.c"
#include "../structures/list_lexeme.h"

void cherche_etiquette(Lexeme_t * head_lexemes, Etiquette_t * list_etiquettes) {
  // Search on list of lexemes and push etiquetes on list
  // of etiquettes

  push(head_lexemes, "salut", 1, 1);

  Lexeme_t * current = next_lexeme(head_lexemes);

  while (current != NULL && next_lexeme(current) != NULL) {
    if (type_lexeme(current) == 1 && type_lexeme(next_lexeme(current)) == 11) { // CAS ETIQUETTES => SYMBOLE :
      if (ligne_lexeme(current) == ligne_lexeme(next_lexeme(current))) {
        push_etiquette(list_etiquettes, strdup(word_lexeme(current)), ligne_lexeme(current));
      }
    }
    current = next_lexeme(current);
  }
}
