#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structures/dicio_directives.h"

enum {START_BSS, SPACE_BSS, ERROR_BSS};

void analyse_bss(Lexeme_t * head_bss, Dicio_Directives_t * dicio_directives) {
  Lexeme_t * current = head_bss;
  int S = START_BSS;
  int type_permit = 0;
  while (next_lexeme(current) != NULL) {
    current = next_lexeme(current);
    switch (S) {
      case START_BSS:
        if (type_lexeme(current) == 3) { // EST DIRECTIVE
          if (is_Dir_in_Dicio_Directives(dicio_directives, word_lexeme(current)) != -1) {
            type_permit = is_Dir_in_Dicio_Directives(dicio_directives, word_lexeme(current));
            S = SPACE_BSS;
            printf("TROUVE SPACE\n");
          }
        }
        else {
          S = ERROR_BSS;
        }
        break;
      case SPACE_BSS:
        if (type_lexeme(current) == type_permit) { // DECIMAL
          printf("ARGUMENT, AJOUT COLL\n");
          S = START_BSS;
        }
        else {
          printf("ligne %d: INCORECT TYPE OF OPERAND FOR => .space <=\n", ligne_lexeme(current));
          S = ERROR_BSS;
        }
        break;
      case ERROR_BSS:
        printf("ERROR\n");
        abort();
        break;
    }
  }
}
