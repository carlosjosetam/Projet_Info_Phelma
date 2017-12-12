#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/dicio_instru.h"
#include "../structures/coll_instru.h"
#include "../structures/list_lexeme.h"
#include "analyse_text.h"
#include "analyse_gramatical_1.h"
#include "../../include/notify.h"

bool is_next_same_line(Lexeme_t * current) {
  if (next_lexeme(current) != NULL) {
    if (type_lexeme(next_lexeme(current)) != 17) {
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
  int type_op1 = -1;
  int type_op2 = -1;
  int type_op3 = -1;
  int decalage = -4;
  int current_line;

  if (next_lexeme(current) == NULL) { /* EXIT, NO .text TERMS */
    return coll_instru;
  }
  else {
    current_line = ligne_lexeme(next_lexeme(current));
  }


  while (next_lexeme(current) != NULL) {

    current = next_lexeme(current);

    if (current_line != ligne_lexeme(current)) { /* Changement de ligne */
      /*printf("*********** NEW LINE ***********\n"); */
      if (!(type_lexeme(current) == 17)) {
        decalage = decalage + 4;
      }
      current_line = ligne_lexeme(current);
    }

    switch (S) {
      case START_TEXT:
      if (type_lexeme(current) == 17) {
        break; /* ignore jump ligne */
      }
        /*printf("START\n"); */
        if (type_lexeme(current) == 1) { /* IS SYMBOLE */
          if (is_Instru_Dicio_Instru(dicio_instru, word_lexeme(current))) {
            n_op = n_op_Dicio_Instru(dicio_instru, word_lexeme(current));
            DEBUG_MSG("%s op %d\n", word_lexeme(current), n_op);
            instru = strdup(word_lexeme(current));

            if (n_op == 0) { /* CASE NOP */
              if (!is_next_same_line(current)) {
                if (strcmp(instru, "NOP") == 0) { /* case NOP -> SLL $0, $0, 0 */
                  push_Coll_INSTRU(coll_instru, "SLL", 3, ligne_lexeme(current), decalage, "$0", "$0", "0", 9, 9, 2);
                  S = START_TEXT; break;
                }

                push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, NULL, NULL, NULL, -1, -1, -1);
                S = START_TEXT; break;
              }
              else {
                WARNING_MSG("line %d: Instruction => %s <= does not have operands", ligne_lexeme(current), instru);
                S = JUMP_TEXT; break;
              }
            }

            if (is_next_same_line(current)) { /* VALIDATE INSTRU */
              /*printf("%s has %d op\n", instru, n_op); */
              S = OP1_TEXT;
              break;
            }
            else {
              WARNING_MSG("line %d: Instruction > %s < without parameters\n", ligne_lexeme(current), word_lexeme(current));
              S = START_TEXT; break;
            }
          }
          else {
            WARNING_MSG("line %d: Instruction > %s < not found in dictionaire\n", ligne_lexeme(current), word_lexeme(current));
            if (is_next_same_line(current)) {
              S = JUMP_TEXT; break;
            }
            else {
              S = START_TEXT; break;
            }
          }
        }
        else {
          ERROR_MSG("line %d: Type > %d < not allowed in .text\n", ligne_lexeme(current), type_lexeme(current));
          if (is_next_same_line(current)) {
            S = JUMP_TEXT; break;
          }
          else {
            S = START_TEXT; break;
          }
          /* CHECK ERROR */
        }
        break;

      case OP1_TEXT:
        /*printf("OP1_TEXT\n"); */
        if (type_lexeme(current) != 4) { /* VERIFICATION OF TYPE (NOT VIRGULE) */
          op1 = strdup(word_lexeme(current)); /* VALIDATED */
          type_op1 = type_lexeme(current);

          if (n_op == 1) { /* SHOULD END HERE */
            if (is_next_same_line(current)) {
              WARNING_MSG("line %d: More elements in line than allowed\n", ligne_lexeme(current));
              S = JUMP_TEXT; break;
            }
            else {
              /* PUSH TO COLL */
              push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, op1, NULL, NULL, type_op1, -1, -1);
              DEBUG_MSG("PUSH TO COLL: %s %s %s %s | decalage: %d\n", instru, op1, NULL, NULL, decalage);
              S = START_TEXT; break; /* DONE */
            }
          }
          else { /* IF N_OP > 1 */
            if (is_next_same_line(current)) {
              S = VIRGULE_1_TEXT; break;
            }
            else {
              WARNING_MSG("line %d: Wrong number of operands for > %s <. Expected %d\n", ligne_lexeme(current), instru, n_op);
              S = START_TEXT; break;
            }
          }
        }
        else {
          WARNING_MSG("line %d: Incorrect operand type > %s < for > %s < \n", ligne_lexeme(current), word_lexeme(current), instru);
          if (is_next_same_line(current)) {
            S = JUMP_TEXT;
            break;
          }
          else {
            S = START_TEXT;
            break;
          }
        }

        break;

      case VIRGULE_1_TEXT:
        /*printf("VIRGULE_1_TEXT\n"); */
        if (type_lexeme(current) == 4) { /* IF ITS VIRGULE */
          if (is_next_same_line(current)) {
            S = OP2_TEXT; break;
          }
          else {
            WARNING_MSG("line %d: Wrong number of operands for > %s <. Expected %d\n", ligne_lexeme(current), instru, n_op);
            S = START_TEXT; break;
          }
        }
        else {
          WARNING_MSG("line %d: Wrong separator for operands. Use virgule > , <\n", ligne_lexeme(current));
          if (is_next_same_line(current)) {
            S = JUMP_TEXT; break;
          }
          else {
            S = START_TEXT; break;
          }
        }
        break;

      case OP2_TEXT:
        /*printf("OP2_TEXT\n"); */
        if (type_lexeme(current) != 4) {
          op2 = strdup(word_lexeme(current)); /* VALIDATED */
          type_op2 = type_lexeme(current);

          if (n_op == 2) {
            if (is_next_same_line(current)) {
              WARNING_MSG("line %d: Wrong number of operands for > %s <. Expected %d\n", ligne_lexeme(current), instru, n_op);
              S = JUMP_TEXT; break;
            }
            else { /*SUCCESS */
              /* PUSH TO COLL */

              /* CASE PSEUDO */
              if (strcmp(instru, "MOVE") == 0) {
                push_Coll_INSTRU(coll_instru, "ADD", 3, ligne_lexeme(current), decalage, op1, op2, "$zero", 9, 9, 9);
                S = START_TEXT; break;
              }

              if (strcmp(instru, "NEG") == 0) {
                push_Coll_INSTRU(coll_instru, "SUB", 3, ligne_lexeme(current), decalage, op1, "$zero", op2, 9, 9, 9);
                S = START_TEXT; break;
              }

              if (strcmp(instru, "LI") == 0) {
                push_Coll_INSTRU(coll_instru, "ADDI", 3, ligne_lexeme(current), decalage, op1, "$zero", op2, 9, 9, 2);
                S = START_TEXT; break;
              }

              /* CASE LW and SW with SYMBOLE */
              if (strcmp(instru, "LW") == 0 && type_op2 == 1) {
                push_Coll_INSTRU(coll_instru, "LUI", 2, ligne_lexeme(current), decalage, "$at", op2, NULL, 9, 1, -1);
                decalage = decalage + 4;
                /* push_Coll_INSTRU(coll_instru, "LW", 2, ligne_lexeme(current), decalage, op1, "0x0($at)", NULL, 9, 18, -1); */
                push_Coll_INSTRU(coll_instru, "LW", 2, ligne_lexeme(current), decalage, op1, op2, NULL, 9, 1, -1);
                S = START_TEXT; break;
              }

              if (strcmp(instru, "SW") == 0 && type_op2 == 1) {
                push_Coll_INSTRU(coll_instru, "LUI", 2, ligne_lexeme(current), decalage, "$at", op2, NULL, 9, 1, -1);
                decalage = decalage + 4;
                /* push_Coll_INSTRU(coll_instru, "SW", 2, ligne_lexeme(current), decalage, op1, "0x0($at)", NULL, 9, 18, -1); */
                push_Coll_INSTRU(coll_instru, "SW", 2, ligne_lexeme(current), decalage, op1, op2, NULL, 9, 1, -1);

                S = START_TEXT; break;
              }

              push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, op1, op2, NULL, type_op1, type_op2, -1);
              DEBUG_MSG("PUSH TO COLL: %s %s %s %s | decalage: %d\n", instru, op1, op2, NULL, decalage);
              S = START_TEXT; break;
            }
          }
          else { /* NOP 3 */
            if (is_next_same_line(current)) {
              S = VIRGULE_2_TEXT; break;
            }
            else {
              WARNING_MSG("line %d: Wrong number of operands for > %s <. Expected %d\n", ligne_lexeme(current), instru, n_op);
              S = START_TEXT; break;
            }
          }
        }
        else {
          WARNING_MSG("line %d: Incorrect operand type > %s < for > %s < \n", ligne_lexeme(current), word_lexeme(current), instru);
          if (is_next_same_line(current)) {
            S = JUMP_TEXT; break;
          }
          else {
            S = START_TEXT; break;
          }
        }

        break;

        case VIRGULE_2_TEXT:
          /*printf("VIRGULE_2_TEXT\n"); */
          if (type_lexeme(current) == 4) { /* IF ITS VIRGULE */
            if (is_next_same_line(current)) {
              S = OP3_TEXT; break;
            }
            else {
              WARNING_MSG("line %d: Wrong number of operands for > %s <. Expected %d\n", ligne_lexeme(current), instru, n_op);
              S = START_TEXT; break;
            }
          }
          else {
            WARNING_MSG("line %d: Wrong separator for operands. Use virgule > , <\n", ligne_lexeme(current));
            if (is_next_same_line(current)) {
              S = JUMP_TEXT; break;
            }
            else {
              S = START_TEXT; break;
            }
          }
          break;

        case OP3_TEXT:
          /*printf("OP3_TEXT\n"); */
          if (type_lexeme(current) != 4) {
            op3 = strdup(word_lexeme(current)); /* VALIDATED */
            type_op3 = type_lexeme(current);

            if (is_next_same_line(current)) {
              WARNING_MSG("line %d: Wrong number of operands for > %s <. Expected %d\n", ligne_lexeme(current), instru, n_op);
              S = JUMP_TEXT; break;
            }
            else {
              /* PUSH TO COLL */

              /*PSEUDO INSTRUCTIONS */
              if (strcmp(instru, "BLT") == 0) {
                push_Coll_INSTRU(coll_instru, "SLT", 3, ligne_lexeme(current), decalage, "$1", op1, op2, 9, 9, 9);
                decalage = decalage + 4;
                push_Coll_INSTRU(coll_instru, "BNE", 3, ligne_lexeme(current), decalage, "$1", "$zero", op3, 9, 9, 1);
                S = START_TEXT; break;
              }


              push_Coll_INSTRU(coll_instru, instru, n_op, ligne_lexeme(current), decalage, op1, op2, op3, type_op1, type_op2, type_op3);
              DEBUG_MSG("PUSH TO COLL: %s %s %s %s | decalage: %d\n", instru, op1, op2, op3, decalage);
              S = START_TEXT; break;
            }
          }
          else {
            WARNING_MSG("line %d: Incorrect operand type > %s < for > %s < \n", ligne_lexeme(current), word_lexeme(current), instru);
            if (is_next_same_line(current)) {
              S = JUMP_TEXT; break;
            }
            else {
              S = START_TEXT; break;
            }
          }
          WARNING_MSG("line %d: Extra element > %s < in line", ligne_lexeme(current), word_lexeme(current));
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
