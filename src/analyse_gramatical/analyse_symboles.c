#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/list_lexeme.h"
#include "analyse_symboles.h"
#include "analyse_text.h"
#include "../../include/notify.h"

enum {START_SYM, SYMBOLE_SYM, MOINS_SYM, VIRGULE_SYM};


  Lexeme_t * analyse_symboles(Lexeme_t * head_lexemes) {
  Lexeme_t * new_lexemes = new_lexeme();
  Lexeme_t * current = head_lexemes;

  int current_line = 0;
  int S = START_SYM;
  int type = 0;


  if (next_lexeme(current) == NULL) { //EXIT, NO .text TERMS
    return new_lexemes;
  }
  else {
    current_line = ligne_lexeme(next_lexeme(current));
  }

  while (next_lexeme(current) != NULL) {
    current = next_lexeme(current);
    if (current_line != ligne_lexeme(current)) { // Changement de ligne
      //DEBUG_MSG("*********** NEW LINE ***********\n");
      current_line = ligne_lexeme(current);
    }

    switch (S) {
      case START_SYM:
      type = type_lexeme(current);
      if (type == 1) { //SYMBOLE
        if (!is_next_same_line(current)) {
          push(new_lexemes, word_lexeme(current), type_lexeme(current), ligne_lexeme(current));
          S = START_SYM;
          break;
        }
        else {
          S = VIRGULE_SYM; // VERIFICATION DE VIRGULE
          break;
        }
      }
      else if (type == 16) { // MOINS
        if (is_next_same_line(current)) {
          S = MOINS_SYM;
          break;
        }
        else {
          ERROR_MSG("line %d: Invalid use of minus => - <=", current_line);
        }
      }
      else if (type== 2 || type == 5 || type == 6 || type == 7) { // NOMBRES

      }
      break;

    }
   }
  return new_lexemes;
}
