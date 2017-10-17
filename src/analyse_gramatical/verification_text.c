#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Lexeme_t * find_text(Lexeme_t * head_lexemes) {
  Lexeme_t * current = head_lexemes;
  if (current->next == NULL) return NULL; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (type_lexeme(current) == 3) { // Case of DIRECTIVE
      if (strcmp(word_lexeme(current), ".text") == 0) {
        printf(".text trouvé en ligne %d\n", ligne_lexeme(current));
        return current;
      }
    }
  }
  return NULL;
}

void verification_text(Lexeme_t * head_lexemes, Dicio_Instru_t * dicio_instru) {
  printf("\nVerification .TEXT en cours...\n");
  Lexeme_t * head_text = find_text(head_lexemes);

  if (head_text == NULL) { // FILE WITHOUT .TEXT
    printf("On n'a pas trouvé => .text <= dans le fichier\n");
    printf("Verifier pour continuer compilation\n");
    abort();
  }
  printf("ADD tem %d ops\n", is_Instru_in_Dicio_Instru(dicio_instru, "ADD"));


}
