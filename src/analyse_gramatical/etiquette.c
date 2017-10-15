#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structures/list_etiquette.h"
#include "../structures/list_etiquette.c"
#include "../structures/list_lexeme.h"

void cherche_etiquette(Lexeme_t * head_lexemes, Etiquette_t * list_etiquettes) {
  // Search on list of lexemes and push etiquetes on list
  // of etiquettes

  Lexeme_t * current = next_lexeme(head_lexemes);

  while (current != NULL && next_lexeme(current) != NULL) {
    if (type_lexeme(current) == 1 && type_lexeme(next_lexeme(current)) == 11) { // CAS ETIQUETTES => SYMBOLE :
      if (ligne_lexeme(current) == ligne_lexeme(next_lexeme(current))) {
        if (is_in_list(list_etiquettes, strdup(word_lexeme(current))) == false) {
          push_etiquette(list_etiquettes, strdup(word_lexeme(current)), ligne_lexeme(current));
        }
        else {
          printf("L'etiquette => %s <= en ligne %d a été declaré plus qu'une fois\n", strdup(word_lexeme(current)), ligne_lexeme(current));
          printf("Corriger pour continuer la compilation\n");
          abort();
        }
      }
    }
    if (type_lexeme(current) == 14 && type_lexeme(next_lexeme(current)) == 11) { // CAS => ERROR :
      printf("L'etiquette => %s <= en ligne %d n'est pas permis\n", strdup(word_lexeme(current)), ligne_lexeme(current));
      printf("Corriger pour continuer la compilation\n");
      abort();
    }
    current = next_lexeme(current);
  }
}
