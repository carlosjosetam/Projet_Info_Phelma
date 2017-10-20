#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structures/list_lexeme.h"
#include "../structures/dicio_instru.h"
#include "division_section.h"

enum {START, TEXT, DATA, BSS};

void division_section(Lexeme_t * head_lexemes, Lexeme_t * head_text, Lexeme_t * head_data, Lexeme_t * head_bss, Dicio_Instru_t * dicio_instru) {
  printf("\nVerification sections en cours...\n");
  if (next_lexeme(head_lexemes) == NULL) { // EVITER DES ERRORS
    return;
  }

  Lexeme_t * current = head_lexemes;
  int S = START;

  while (next_lexeme(current) != NULL) {
    current = next_lexeme(current);
    switch (S) {
      case START:
        if (strcmp(word_lexeme(current), ".data") == 0) { //TROUVE .data
          //printf("In DATA section =>>\n");
          S = DATA; break;
        }
        else if (strcmp(word_lexeme(current), ".bss") == 0) { //TROUVE .bss
          //printf("In BSS section =>>\n");
          S = BSS; break;
        }
        else { //TEXT section
          //printf("In TEXT section =>>\n");
          if (strcmp(word_lexeme(current), ".text") != 0){
            //printf("%s\n", word_lexeme(current));
            push(head_text, strdup(word_lexeme(current)), type_lexeme(current), ligne_lexeme(current));
          }
          S = TEXT; break; break; break;
        }
        break;

      case TEXT:
        if (strcmp(word_lexeme(current), ".data") == 0) { //TROUVE .data
          //printf("In DATA section =>>\n");
          S = DATA; break; break;
        }
        else if (strcmp(word_lexeme(current), ".bss") == 0) { //TROUVE .bss
          //printf("In BSS section =>>\n");
          S = BSS; break;
        }
        else {
          //printf("%s\n", word_lexeme(current));
          push(head_text, strdup(word_lexeme(current)), type_lexeme(current), ligne_lexeme(current));
        }
        break;

      case DATA:
        if (strcmp(word_lexeme(current), ".text") == 0) { //TROUVE .text
          //printf("In TEXT section =>>\n");
          S = TEXT; break; break;
        }
        else if (strcmp(word_lexeme(current), ".bss") == 0) { //TROUVE .bss
          //printf("In BSS section =>>\n");
          S = BSS; break;
        }
        else {
          //printf("%s\n", word_lexeme(current));
          push(head_data, strdup(word_lexeme(current)), type_lexeme(current), ligne_lexeme(current));
        }
        break;

      case BSS:
        if (strcmp(word_lexeme(current), ".text") == 0) { //TROUVE .text
          //printf("In TEXT section =>>\n");
          S = TEXT; break; break;
        }
        else if (strcmp(word_lexeme(current), ".data") == 0) { //TROUVE .data
          //printf("In DATA section =>>\n");
          S = DATA; break;
        }
        else {
          //printf("%s\n", word_lexeme(current));
          push(head_bss, strdup(word_lexeme(current)), type_lexeme(current), ligne_lexeme(current));
        }
        break;
    }
  }
}
