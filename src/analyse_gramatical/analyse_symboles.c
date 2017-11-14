#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/list_lexeme.h"
#include "analyse_symboles.h"
#include "analyse_text.h"
#include "../../include/notify.h"

enum {START_SYM, SYMBOLE_SYM, MOINS_SYM, BASE_SYM, NOMBRE_SYM};


  Lexeme_t * analyse_symboles(Lexeme_t * head_lexemes) {
  Lexeme_t * new_lexemes = new_lexeme();
  Lexeme_t * current = head_lexemes;

  int current_line = 0;
  int S = START_SYM;
  int type = 0;
  char * new_symbole;

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
      new_symbole = word_lexeme(current);
      type = type_lexeme(current);

      if (type == 16) { // MOINS
        S = MOINS_SYM; break;
      }
      else if (type== 2 || type == 5 || type == 6 || type == 7) { // NOMBRES
        S = NOMBRE_SYM; break;
      }
      else {
        push(new_lexemes, word_lexeme(current), type_lexeme(current), ligne_lexeme(current));
      }
      break;

      case NOMBRE_SYM:
      if (type_lexeme(current) == 17 || type_lexeme(current) == 4) { // NL or VIRGULE
        push(new_lexemes, new_symbole, type, ligne_lexeme(current));
        push(new_lexemes, word_lexeme(current), type_lexeme(current), ligne_lexeme(current));
        S = START_SYM; break;
      }
      if (type_lexeme(current) == 12) {
        strcat(new_symbole, word_lexeme(current));
        S = BASE_SYM; break;
      }
      else {
        ERROR_MSG("line %d: incorrect use of symbole", ligne_lexeme(current));
      }
      break;

      case MOINS_SYM:
      type = type_lexeme(current);
      if (type== 2 || type == 5 || type == 6 || type == 7) {
        strcat(new_symbole, word_lexeme(current));
        S = NOMBRE_SYM; break;
      }
      else {
        ERROR_MSG("line %d: Expected number after minus => - <=", ligne_lexeme(current));
      }
      break;

      case BASE_SYM:
      if (is_next_same_line(current)) { // check if we may have a )
        if (type_lexeme(current) == 9 && type_lexeme(next_lexeme(current)) == 13) { /* if we have REGISTRE PAR_DRO */
          strcat(new_symbole, word_lexeme(current));
          strcat(new_symbole, word_lexeme(next_lexeme(current)));
          push(new_lexemes, new_symbole, 18, ligne_lexeme(current));
        }
        else {
          ERROR_MSG("line %d: Error 1 of Base_offset description", ligne_lexeme(current));
        }
        if (!is_next_same_line(next_lexeme(current))) {
          current = next_lexeme(current);
          S = START_SYM; break;
        }
        else {
          ERROR_MSG("line %d: Error of Base_offset description", ligne_lexeme(current));
        }
        break;
      }
    }
   }
  return new_lexemes;
}
