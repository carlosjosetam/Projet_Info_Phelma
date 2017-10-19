#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/dicio_directives.h"
#include "../structures/coll_data.h"
#include "../structures/list_lexeme.h"
#include "analyse_data.h"

// STILL CONSIDERS THAT WE HAVE ONLY TWO TERMS PER LIGNE

enum {START_DATA, DIR_DATA, SPACE_DATA, BYTE_DATA, WORD_DATA, ASCIIZ_DATA, ERROR_DATA};

Coll_DATA_t * analyse_data(Lexeme_t * head_data, Dicio_Directives_t * dicio_directives) {
  Coll_DATA_t * coll_data = new_Coll_DATA();
  Lexeme_t * current = head_data;
  int S = START_DATA;
  int type_permit = 0;
  char * directive;
  int ver_ligne = ligne_lexeme(next_lexeme(current));
  int decalage = 0;
  while (next_lexeme(current) != NULL) {

     // if there was an error, starts verification
    current = next_lexeme(current);


    if (ver_ligne != ligne_lexeme(current)) { // Changement de ligne
      decalage = decalage + 4;
      ver_ligne = ligne_lexeme(current);
    }
    switch (S) {
      case START_DATA:
        if (type_lexeme(current) == 3) { // EST DIRECTIVE
          if (is_Dir_in_Dicio_Directives(dicio_directives, word_lexeme(current))) { // IF IN DICIONIRE
            if (next_lexeme(current) != NULL) {
              directive = strdup(word_lexeme(current));
              type_permit = type_permit_directive(dicio_directives, word_lexeme(current));
              // VERIFY DIRECTIVE
              S = DIR_DATA;
              break;

              //VOIR COMMENT VERIFIER PLUS DE CHOSES, TYPE DE VALEUR, ADEQUATE
              /*if (strcmp(directive, ".space") == 0) {
                S = SPACE_DATA;
              }
              else if (strcmp(directive, ".byte") == 0) {
                S = BYTE_DATA;
              }
              else if (strcmp(directive, ".word") == 0) {
                S = WORD_DATA;
              }
              else if (strcmp(directive, ".asciiz") == 0) {
                S = ASCIIZ_DATA;
              }*/

            }
            else {
              printf("ligne %d: DIRECTIVE => %s <= DOES NOT HAVE OPERANDS\n", ligne_lexeme(current), word_lexeme(current));
            }
          }
          else { // ERROR OF DIRECTIVE
            printf("ligne %d: DIRECTIVE => %s <= NOT ALOWED IN .DATA\n", ligne_lexeme(current), word_lexeme(current));
            printf("VERIFY THIS ERROR TO CONTINUE... ABORT\n");
            abort();
          }
        }
        else { // ERROR OF TYPE
          printf("ligne %d: ERROR OF SYNTAXE. => %s <= TYPE => %d <= NOT ALLOWED IN .DATA\n", ligne_lexeme(current), word_lexeme(current), type_lexeme(current));
          printf("VERIFY THIS ERROR TO CONTINUE... ABORT\n");
          abort();
        }
        break;
      case DIR_DATA:
        if (is_type_permit_directive(dicio_directives, directive, type_lexeme(current))) { // DECIMAL. ADD TO COLL
          //printf("ARGUMENT, AJOUT COLL\n");
          //printf("decalage: %d\n", decalage);
          push_Coll_DATA(coll_data, directive, 1, ligne_lexeme(current), decalage, atoi(word_lexeme(current)));
          S = START_DATA;
          if (next_lexeme(current) != NULL) {
            if (type_lexeme(next_lexeme(current)) == 4) { // VIRGULE APRES -> MORE THAN ONE OPERAND
              printf("ligne %d: ONLY 1 OPERAND FOR => %s <= IS ALLOWED\n", ligne_lexeme(current), directive);
            }
          }
        }
        else {
          printf("ligne %d: INCORECT TYPE (%d) OF OPERAND => %s <= FOR => %s <=\n", ligne_lexeme(current), type_lexeme(current), word_lexeme(current), directive);
        }
        break;
      case ERROR_DATA:
        //printf("VERIFY THE ERRORS TO CONTINUE... ABORT\n");
        break;
        //abort();
    }
  }
  if (S == ERROR_DATA) {
    printf("VERIFY THE ERRORS TO CONTINUE... ABORT\n");
    //abort();
  }
  return coll_data;
}
