#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/list_lexeme.h"
#include "../structures/list_etiquette.h"
#include "etiquette.h"

void cherche_etiquette(Lexeme_t * head_lexemes, Etiquette_t * list_etiquettes, char * section) {
  // Search on list of lexemes and push etiquetes on list
  // of etiquettes
  if (next_lexeme(head_lexemes) == NULL) { // case of section EMPTY
    return;
  }

  Lexeme_t * current = next_lexeme(head_lexemes);
  Lexeme_t * before_current = head_lexemes;
  int decalage = 0;
  int ver_ligne = ligne_lexeme(current);
  while (current != NULL && next_lexeme(current) != NULL) {
    if (ver_ligne != ligne_lexeme(current)) { // Changement de ligne
      decalage = decalage + 4;
      ver_ligne = ligne_lexeme(current);
    }
    if (type_lexeme(current) == 1 && type_lexeme(next_lexeme(current)) == 11) { // CAS ETIQUETTES => SYMBOLE :
      if (ligne_lexeme(current) == ligne_lexeme(next_lexeme(current))) {
        if (is_in_list(list_etiquettes, strdup(word_lexeme(current))) == false) {
          push_etiquette(list_etiquettes, strdup(word_lexeme(current)), ligne_lexeme(current), decalage, section);
          DEBUG_MSG("Trouvé etiquette => %s <= en ligne %d\n", strdup(word_lexeme(current)), ligne_lexeme(current));
          effacer_2(before_current);
          current = next_lexeme(before_current);
        }
        else {
          ERROR_MSG("L'etiquette => %s <= en ligne %d a été declaré plus qu'une fois\n", strdup(word_lexeme(current)), ligne_lexeme(current));
          //abort();
        }
      }
    }
    else if (type_lexeme(current) == 14 && type_lexeme(next_lexeme(current)) == 11) { // CAS => ERROR :
      ERROR_MSG("L'etiquette => %s <= en ligne %d n'est pas permit\n", strdup(word_lexeme(current)), ligne_lexeme(current));
      //abort();
    }
    else {
      current = next_lexeme(current);
      before_current = next_lexeme(before_current);
    }

  }
  print_list_etiquette(list_etiquettes);
}
