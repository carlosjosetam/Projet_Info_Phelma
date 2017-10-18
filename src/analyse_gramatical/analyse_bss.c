#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structures/dicio_directives.h"
#include "../structures/coll_bss.h"

enum {START_BSS, SPACE_BSS, ERROR_BSS};

Coll_BSS_t * analyse_bss(Lexeme_t * head_bss, Dicio_Directives_t * dicio_directives) {
  Coll_BSS_t * coll_bss = new_Coll_BSS();
  Lexeme_t * current = head_bss;
  int S = START_BSS;
  int type_permit = 0;
  char * directive;
  int ver_ligne = ligne_lexeme(next_lexeme(current));
  int decalage = 0;
  while (next_lexeme(current) != NULL) {
    current = next_lexeme(current);
    if (ver_ligne != ligne_lexeme(current)) { // Changement de ligne
      decalage = decalage + 4;
      ver_ligne = ligne_lexeme(current);
    }
    switch (S) {
      case START_BSS:
        if (type_lexeme(current) == 3) { // EST DIRECTIVE
          if (strcmp(word_lexeme(current), ".space") == 0) { // ONLY SPACE ALLOWED
            if (next_lexeme(current) != NULL) {
              S = SPACE_BSS;
              directive = strdup(word_lexeme(current));
              type_permit = type_permit_directive(dicio_directives, word_lexeme(current));
              //printf("TROUVE POSSIBLE .SPACE\n");
            }
            else {
              printf("ligne %d: DIRECTIVE => %s <= DOES NOT HAVE OPERANDS\n", ligne_lexeme(current), word_lexeme(current));
              S = ERROR_BSS;
            }
          }
          else { // ERROR OF DIRECTIVE
            printf("ligne %d: DIRECTIVE => %s <= NOT ALOWED IN .BSS\n", ligne_lexeme(current), word_lexeme(current));
            S = ERROR_BSS;
          }
        }
        else { // ERROR OF TYPE
          printf("ligne %d: ERROR OF SYNTAXE. => %s <= TYPE => %d <= NOT ALLOWED IN .BSS\n", ligne_lexeme(current), word_lexeme(current), type_lexeme(current));
          S = ERROR_BSS;
        }
        break;
      case SPACE_BSS:
        if (type_lexeme(current) == type_permit) { // DECIMAL. ADD TO COLL
          //printf("ARGUMENT, AJOUT COLL\n");
          //printf("decalage: %d\n", decalage);
          push_Coll_BSS(coll_bss, directive, 1, ligne_lexeme(current), decalage, atoi(word_lexeme(current)));
          S = START_BSS;
          if (next_lexeme(current) != NULL) {
            if (type_lexeme(next_lexeme(current)) == 4) { // VIRGULE APRES -> MORE THAN ONE OPERAND
              printf("ligne %d: ONLY 1 OPERAND FOR => .space <= IS ALLOWED\n", ligne_lexeme(current));
              S = ERROR_BSS;
            }
          }
        }
        else {
          printf("ligne %d: INCORECT TYPE OF OPERAND FOR => .space <=\n", ligne_lexeme(current));
          S = ERROR_BSS;
        }
        break;
      case ERROR_BSS:
        printf("VERIFY THE ERRORS TO CONTINUE... ABORT\n");
        abort();
        break;
    }
  }
  return coll_bss;
}
