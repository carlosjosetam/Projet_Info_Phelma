#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/dicio_instru.h"
#include "../structures/coll_instru.h"
#include "../structures/list_lexeme.h"
#include "analyse_text.h"
#include "analyse_gramatical_1.h" //

bool is_next_same_line(Lexeme_t * current, int current_line) {
  if (next_lexeme(current) != NULL) {
    if (ligne_lexeme(next_lexeme(current)) == current_line) {
      return true;
    }
  }
  return false;
}

enum {START_TEXT, OP1_TEXT, VIRGULE_1_TEXT, OP2_TEXT, VIRGULE_2_TEXT, OP3_TEXT, JUMP_TEXT};

Coll_INSTRU_t * analyse_text(Lexeme_t * head_text, Dicio_Instru_t * dicio_instru) {
  Lexeme_t * current = head_text;
  Coll_INSTRU_t * coll_instru = new_Coll_INSTRU();
  int S = START_TEXT;
  int n_op = 0;
  char * instru = NULL;
  char * op1 = NULL;
  char * op2 = NULL;
  char * op3 = NULL;
  int decalage = 0;
  int current_line;

  if (next_lexeme(current) == NULL) { //EXIT, NO .text TERMS
    return coll_instru;
  }
  else {
    current_line = ligne_lexeme(next_lexeme(current));
  }


  while (next_lexeme(current) != NULL) {

    current = next_lexeme(current);

    if (current_line != ligne_lexeme(current)) { // Changement de ligne
      printf("*********** NEW LINE ***********\n");
      decalage = decalage + 4;
      current_line = ligne_lexeme(current);
    }

    switch (S) {
      case START_TEXT:
        printf("START\n");
        if (type_lexeme(current) == 1) { // IS SYMBOLE
          if (is_Instru_Dicio_Instru(dicio_instru, word_lexeme(current))) {
            if (is_next_same_line(current, current_line)) { // VALIDATE INSTRU
              n_op = n_op_Dicio_Instru(dicio_instru, word_lexeme(current));
              instru = strdup(word_lexeme(current));
              printf("%s has %d op\n", instru, n_op);
              S = OP1_TEXT;
              break;
            }
            else {
              printf("line %d: INSTRUCTION > %s < without parameters\n", ligne_lexeme(current), word_lexeme(current));
              S = START_TEXT; break;
            }
          }
          else {
            printf("line %d: INSTRUCTION > %s < not in dicitionaire\n", ligne_lexeme(current), word_lexeme(current));
            if (is_next_same_line(current, current_line)) {
              S = JUMP_TEXT; break;
            }
            else {
              S = START_TEXT; break;
            }
          }
        }
        else {
          printf("line %d: TYPE > %d < not allowed in .text\n", ligne_lexeme(current), type_lexeme(current));
          if (is_next_same_line(current, current_line)) {
            S = JUMP_TEXT; break;
          }
          else {
            S = START_TEXT; break;
          }
          // CHECK ERROR
        }
        break;

      case OP1_TEXT:
        printf("OP1_TEXT\n");
        if (type_lexeme(current) != 4) { // VERIFICATION OF TYPE (NOT VIRGULE)
          op1 = strdup(word_lexeme(current)); // VALIDATED

          if (n_op == 1) { // SHOULD END HERE
            if (is_next_same_line(current, current_line)) {
              printf("MORE ELEMENTS IN LINE\n");
              S = JUMP_TEXT; break;
            }
            else {
              // PUSH TO COLL
              push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, op1, NULL, NULL);
              printf("PUSH TO COLL: %s %s %s %s | decalage: %d\n", instru, op1, NULL, NULL, decalage);
              S = START_TEXT; break; // DONE
            }
          }
          else { // IF N_OP > 1
            if (is_next_same_line(current, current_line)) {
              S = VIRGULE_1_TEXT; break;
            }
            else {
              printf("line %d: wrong number of operands\n");
              S = START_TEXT; break;
            }
          }
        }
        else {
          if (is_next_same_line(current, current_line)) {
            printf("line %d: incorrect operand \n", ligne_lexeme(current));
            S = JUMP_TEXT;
            break;
          }
          else {
            printf("line %d: incorrect operand\n", ligne_lexeme(current));
            S = START_TEXT;
            break;
          }
        }

        break;

      case VIRGULE_1_TEXT:
        printf("VIRGULE_1_TEXT\n");
        if (type_lexeme(current) == 4) { // IF ITS VIRGULE
          if (is_next_same_line(current, current_line)) {
            S = OP2_TEXT; break;
          }
          else {
            printf("line %d: wrong number of operands (less than expected)\n", ligne_lexeme(current));
            S = START_TEXT; break;
          }
        }
        else {
          printf("line %d: WRONG SEPARATOR FOR OPERANDS\n", ligne_lexeme(current));
          if (is_next_same_line(current, current_line)) {
            S = JUMP_TEXT; break;
          }
          else {
            S = START_TEXT; break;
          }
        }
        break;

      case OP2_TEXT:
        printf("OP2_TEXT\n");
        if (type_lexeme(current) != 4) {
          op2 = strdup(word_lexeme(current)); // VALIDATED

          if (n_op == 2) {
            if (is_next_same_line(current, current_line)) {
              printf("line %d: more operands than allowed\n", ligne_lexeme(current));
              S = JUMP_TEXT; break;
            }
            else { //SUCCESS
              // PUSH TO COLL
              push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, op1, op2, NULL);
              printf("PUSH TO COLL: %s %s %s %s | decalage: %d\n", instru, op1, op2, NULL, decalage);
              S = START_TEXT; break;
            }
          }
          else { // NOP 3
            if (is_next_same_line(current, current_line)) {
              S = VIRGULE_2_TEXT; break;
            }
            else {
              printf("line %d: wrong number of operands\n", ligne_lexeme(current));
              S = START_TEXT; break;
            }
          }
        }
        else {
          printf("line %d: incorrect type of operand\n", ligne_lexeme(current));
          if (is_next_same_line(current, current_line)) {
            S = JUMP_TEXT; break;
          }
          else {
            S = START_TEXT; break;
          }
        }

        break;

        case VIRGULE_2_TEXT:
          printf("VIRGULE_2_TEXT\n");
          if (type_lexeme(current) == 4) { // IF ITS VIRGULE
            if (is_next_same_line(current, current_line)) {
              S = OP3_TEXT; break;
            }
            else {
              printf("line %d: wrong number of operands (less than expected)\n", ligne_lexeme(current));
              S = START_TEXT; break;
            }
          }
          else {
            printf("line %d: WRONG SEPARATOR FOR OPERANDS\n", ligne_lexeme(current));
            if (is_next_same_line(current, current_line)) {
              S = JUMP_TEXT; break;
            }
            else {
              S = START_TEXT; break;
            }
          }
          break;

        case OP3_TEXT:
          printf("OP3_TEXT\n");
          if (type_lexeme(current) != 4) {
            op3 = strdup(word_lexeme(current)); // VALIDATED
            if (is_next_same_line(current, current_line)) {
              printf("line %d: incorrect number of operands (more than expected)\n", ligne_lexeme(current));
              S = JUMP_TEXT; break;
            }
            else {
              // PUSH TO COLL
              push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, op1, op2, op3);
              printf("PUSH TO COLL: %s %s %s %s | decalage: %d\n", instru, op1, op2, op3, decalage);
              S = START_TEXT; break;
            }
          }
          else {
            printf("line %d: incorrect type of operand\n", ligne_lexeme(current));
            if (is_next_same_line(current, current_line)) {
              S = JUMP_TEXT; break;
            }
            else {
              S = START_TEXT; break;
            }
          }
          printf("%s\n", word_lexeme(current));
          break;

        case JUMP_TEXT:
          if (next_lexeme(current) != NULL) {
            if (ligne_lexeme(next_lexeme(current)) != current_line) {
              S = START_TEXT;
              break;
            }
          }
          break;
    }
  }
  return coll_instru;
}
