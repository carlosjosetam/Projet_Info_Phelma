#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/dicio_directives.h"
#include "../structures/coll_data.h"
#include "../structures/list_lexeme.h"
#include "analyse_data.h"
#include "analyse_text.h"
#include "../../include/notify.h"

enum {START_DATA, OP1_DATA, JUMP_DATA};


Coll_DATA_t * analyse_data(Lexeme_t * head_data, Dicio_Directives_t * dicio_directives) {
  Lexeme_t * current = head_data;
  Coll_DATA_t * coll_data = new_Coll_DATA();
  int S = START_DATA;
  int n_op = 1;
  char * directive = NULL;
  char * op1 = NULL;
  int decalage = 0;
  int current_line = ligne_lexeme(next_lexeme(current));

  while (next_lexeme(current) != NULL) {

    current = next_lexeme(current);

    if (current_line != ligne_lexeme(current)) { // Changement de ligne
      //printf("*********** NEW LINE ***********\n");
      decalage = decalage + 4;
      current_line = ligne_lexeme(current);
    }

    switch (S) {
      case START_DATA:
        //printf("START\n");
        if (type_lexeme(current) == 3) { // IS DIRECTIVE
          if (is_Dir_in_Dicio_Directives(dicio_directives, word_lexeme(current))) {
            if (is_next_same_line(current, current_line)) { // VALIDATE DIRECTIVE
              directive = strdup(word_lexeme(current));
              //printf("directive => %s\n", directive);
              S = OP1_DATA;
              break;
            }
            else {
              WARNING_MSG("line %d: Directive > %s < without parameters\n", ligne_lexeme(current), word_lexeme(current));
              S = START_DATA; break;
            }
          }
          else {
            ERROR_MSG("line %d: Directive > %s < not allowed in .data\n", ligne_lexeme(current), word_lexeme(current));
            if (is_next_same_line(current, current_line)) {
              S = JUMP_DATA; break;
            }
            else {
              S = START_DATA; break;
            }
          }
        }
        else {
          ERROR_MSG("line %d: Type > %d < not allowed in .data\n", ligne_lexeme(current), type_lexeme(current));
          if (is_next_same_line(current, current_line)) {
            S = JUMP_DATA; break;
          }
          else {
            S = START_DATA; break;
          }
          // CHECK ERROR
        }
        break;

      case OP1_DATA:
        //printf("OP1_DATA\n");
        printf("%s | %d | %s\n", word_lexeme(current), type_lexeme(current), directive);
        if (is_type_permit_directive(dicio_directives, directive, type_lexeme(current))) { // VERIFICATION OF TYPE
          if (is_value_permit_directive(dicio_directives, directive, type_lexeme(current), word_lexeme(current))) { // VERIFICATION OF VALUE
            op1 = strdup(word_lexeme(current)); // VALIDATED

            if (is_next_same_line(current, current_line)) {
              WARNING_MSG("line %d: More elements in line than allowed\n");
              S = JUMP_DATA; break;
            }
            else {
              // PUSH TO COLL
              push_Coll_DATA(coll_data, directive, n_op, ligne_lexeme(current), decalage, op1);
              DEBUG_MSG("PUSH TO COLL: %s %s | decalage: %d\n", directive, op1, decalage);
              S = START_DATA; break; // DONE
            }
          }
          else {
            WARNING_MSG("line %d: Incorect value > %s < for > %s <\n", ligne_lexeme(current), word_lexeme(current), directive);
            if (is_next_same_line(current, current_line)) {
              S = JUMP_DATA; break;
            }
            else {
              S = START_DATA; break;
            }
          }
        }
        else {
          WARNING_MSG("line %d: Incorrect operand > %s < for > %s < \n", ligne_lexeme(current), word_lexeme(current), directive);
          if (is_next_same_line(current, current_line)) {
            S = JUMP_DATA; break;
          }
          else {
            S = START_DATA; break;
          }
        }
        break;

        case JUMP_DATA:
          if (next_lexeme(current) != NULL) {
            if (ligne_lexeme(next_lexeme(current)) != current_line) {
              S = START_DATA;
              break;
            }
          }
          WARNING_MSG("line %d: Extra element > %s < in line", ligne_lexeme(current), word_lexeme(current));
          break;
    }
  }
  return coll_data;
}
