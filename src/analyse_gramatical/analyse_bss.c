#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/dicio_directives.h"
#include "../structures/coll_bss.h"
#include "../structures/list_lexeme.h"
#include "analyse_bss.h"
#include "analyse_text.h"
#include "../../include/notify.h"

enum {START_BSS, OP1_BSS, JUMP_BSS};


Coll_BSS_t * analyse_bss(Lexeme_t * head_bss, Dicio_Directives_t * dicio_directives) {
  Lexeme_t * current = head_bss;
  Coll_BSS_t * coll_bss = new_Coll_BSS();
  int S = START_BSS;
  int n_op = 1;
  char * directive = NULL;
  char * op1 = NULL;
  int decalage = 0;
  int current_line = ligne_lexeme(next_lexeme(current));

  while (next_lexeme(current) != NULL) {

    current = next_lexeme(current);

    if (current_line != ligne_lexeme(current)) { // Changement de ligne
      //DEBUG_MSG("*********** NEW LINE ***********\n");
      decalage = decalage + 4;
      current_line = ligne_lexeme(current);
    }

    switch (S) {
      case START_BSS:
        //DEBUG_MSG("START_BSS\n");
        if (type_lexeme(current) == 3) { // IS DIRECTIVE
          if (strcmp(word_lexeme(current), ".space") == 0) { // ONLY SPACE ALLOWED
            if (is_next_same_line(current, current_line)) { // VALIDATE DIRECTIVE
              directive = strdup(word_lexeme(current));
              //DEBUG_MSG("directive => %s\n", directive);
              S = OP1_BSS;
              break;
            }
            else {
              WARNING_MSG("line %d: Directive > %s < without parameters\n", ligne_lexeme(current), word_lexeme(current));
              S = START_BSS; break;
            }
          }
          else {
            ERROR_MSG("line %d: Directive > %s < not allowed in .bss\n", ligne_lexeme(current), word_lexeme(current));
            if (is_next_same_line(current, current_line)) {
              S = JUMP_BSS; break;
            }
            else {
              S = START_BSS; break;
            }
          }
        }
        else {
          ERROR_MSG("line %d: Type > %d < not allowed in .bss\n", ligne_lexeme(current), type_lexeme(current));
          if (is_next_same_line(current, current_line)) {
            S = JUMP_BSS; break;
          }
          else {
            S = START_BSS; break;
          }
          // CHECK ERROR
        }
        break;

      case OP1_BSS:
        printf("OP1_BSS\n");
        if (is_type_permit_directive(dicio_directives, directive, type_lexeme(current))) { // VERIFICATION OF TYPE
          if (is_value_permit_directive(dicio_directives, directive, type_lexeme(current), word_lexeme(current))) { // VERIFICATION OF VALUE
            op1 = strdup(word_lexeme(current)); // VALIDATED

            if (is_next_same_line(current, current_line)) {
              WARNING_MSG("line %d: More elements in line than allowed\n");
              S = JUMP_BSS; break;
            }
            else {
              // PUSH TO COLL
              push_Coll_BSS(coll_bss, directive, n_op, ligne_lexeme(current), decalage, op1);
              DEBUG_MSG("PUSH TO COLL: %s %s | decalage: %d\n", directive, op1, decalage);
              S = START_BSS; break; // DONE
            }
          }
          else {
            WARNING_MSG("line %d: Incorect value > %s < for > %s <\n", ligne_lexeme(current), word_lexeme(current), directive);
            if (is_next_same_line(current, current_line)) {
              S = JUMP_BSS; break;
            }
            else {
              S = START_BSS; break;
            }
          }
        }
        else {
          WARNING_MSG("line %d: Incorrect operand > %s < for > %s < \n", ligne_lexeme(current), word_lexeme(current), directive);
          if (is_next_same_line(current, current_line)) {
            S = JUMP_BSS; break;
          }
          else {
            S = START_BSS; break;
          }
        }
        break;

        case JUMP_BSS:
          if (next_lexeme(current) != NULL) {
            if (ligne_lexeme(next_lexeme(current)) != current_line) {
              S = START_BSS;
              break;
            }
          }
          WARNING_MSG("line %d: Extra element > %s < in line", ligne_lexeme(current), word_lexeme(current));
          break;
    }
  }
  return coll_bss;
}
