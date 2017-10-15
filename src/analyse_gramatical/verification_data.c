#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Lexeme_t * find_data(Lexeme_t * head_lexemes) {
  Lexeme_t * current = head_lexemes;
  if (current->next == NULL) return NULL; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (type_lexeme(current) == 3) { // Case of DIRECTIVE
      if (strcmp(word_lexeme(current), ".data") == 0) {
        printf(".data trouvé en ligne %d\n", ligne_lexeme(current));
        return current;
      }
    }
  }
  return NULL;
}

void verification_data(Lexeme_t * head_lexemes, Dicio_Instru_t * dicio_instru) {
  printf("\nVerification .DATA en cours...\n");
  Lexeme_t * head_text = find_data(head_lexemes);
  if (head_text == NULL) {
    printf("On n'a pas trouvé => .data <= dans le fichier\n");
    printf("Verifier pour continuer compilation\n");
    abort();
  }
}
