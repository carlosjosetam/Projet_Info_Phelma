#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/list_lexeme.h"
#include "../structures/list_etiquette.h"
#include "../structures/coll_bss.h"
#include "../structures/coll_instru.h"
#include "../structures/coll_data.h"

#include "etiquette.h"

void cherche_etiquette(Lexeme_t * head_lexemes, Etiquette_t * list_etiquettes, char * section) {
  // Search on list of lexemes and push etiquetes on list
  // of etiquettes
  if (next_lexeme(head_lexemes) == NULL) { // case of section EMPTY
    return;
  }

  Lexeme_t * current = next_lexeme(head_lexemes);
  Lexeme_t * before_current = head_lexemes;
  Lexeme_t * atributte = NULL;
  int decalage = 0;
  int ver_ligne = ligne_lexeme(current);
  while (current != NULL && next_lexeme(current) != NULL) {
    if (ver_ligne != ligne_lexeme(current)) { // Changement de ligne
      if (!(type_lexeme(current) == 17 || (type_lexeme(current) == 1 && type_lexeme(next_lexeme(current)) == 11))) {
        decalage = decalage + 4;
      }
      ver_ligne = ligne_lexeme(current);
    }
    if (type_lexeme(current) == 1 && type_lexeme(next_lexeme(current)) == 11) { // CAS ETIQUETTES => SYMBOLE :
      if (ligne_lexeme(current) == ligne_lexeme(next_lexeme(current))) {
        if (is_in_list(list_etiquettes, strdup(word_lexeme(current))) == false) {

          // TO CORRECT LINE
          atributte = next_lexeme(next_lexeme(current));
          if (atributte != NULL) {
            if (type_lexeme(atributte) == 17) { // IF SKIP LINE
              while (next_lexeme(atributte) != NULL) {
                if (type_lexeme(atributte) != 17) {
                  push_etiquette(list_etiquettes, strdup(word_lexeme(current)), ligne_lexeme(next_lexeme(atributte)), decalage, section);
                  DEBUG_MSG("Trouvé etiquette => %s <= en ligne %d\n", strdup(word_lexeme(current)), ligne_lexeme(next_lexeme(atributte)));
                  break;
                }
                else {
                  atributte = next_lexeme(atributte);
                }
              }
            }
            else {
              push_etiquette(list_etiquettes, strdup(word_lexeme(current)), ligne_lexeme(atributte), decalage, section);
              DEBUG_MSG("Trouvé etiquette => %s <= en ligne %d\n", strdup(word_lexeme(current)), ligne_lexeme(atributte));
            }
          }

          effacer_2(before_current);
          current = next_lexeme(before_current);
        }
        else {
          ERROR_MSG("line %d: Etiquette => %s <= has been already declared\n", ligne_lexeme(current), strdup(word_lexeme(current)));
          //abort();
        }
      }
    }
    else if (type_lexeme(current) != 1 && type_lexeme(next_lexeme(current)) == 11) { // CAS => ERROR :
      ERROR_MSG("line %d: Etiquette => %s <= not allowed\n", ligne_lexeme(current), strdup(word_lexeme(current)));
      //abort();
    }
    else {
      current = next_lexeme(current);
      before_current = next_lexeme(before_current);
    }

  }
  print_list_etiquette(list_etiquettes);
}

void update_address_etiquettes(Etiquette_t * list_etiquettes, Coll_BSS_t * coll_bss, Coll_INSTRU_t * coll_instru, Coll_DATA_t * coll_data) {
  if (next_lexeme(list_etiquettes) == NULL) { // case of section EMPTY
    return;
  }

  Etiquette_t * current = get_next_etiquette(list_etiquettes);
  int new_address = 0;

  while (current != NULL) {

    if (strcmp(get_section_etiquette(current), "bss") == 0) {
      new_address = get_address_by_line_bss(coll_bss, get_line_etiquette(current));
      update_address_etiquette(current, new_address);
    }

    if (strcmp(get_section_etiquette(current), "text") == 0) {
      new_address = get_address_by_line_text(coll_instru, get_line_etiquette(current));
      update_address_etiquette(current, new_address);
    }

    if (strcmp(get_section_etiquette(current), "data") == 0) {
      new_address = get_address_by_line_data(coll_data, get_line_etiquette(current));
      update_address_etiquette(current, new_address);
    }

    current = get_next_etiquette(current);
  }
}
