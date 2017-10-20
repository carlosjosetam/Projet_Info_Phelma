#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dicio_instru.h"

void print_Dicio_Instru(Dicio_Instru_t * head) {
  // Print all elements on list
  Dicio_Instru_t * current = head->next;

  printf("\nDICIONAIRE DE INSTRUCTIONS ==>>\n");

  while (current != NULL) {
    printf("%s | n_op: %d | bin: %d\n", current->word, current->n_op, current->code_bin);
    current = current->next;
  }
  printf("\n");
}

int n_op_Dicio_Instru(Dicio_Instru_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false

  Dicio_Instru_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->n_op;
    }
  }
  return -1;
}

bool is_Instru_Dicio_Instru(Dicio_Instru_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false

  Dicio_Instru_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}


void push_Dicio_Instru(Dicio_Instru_t * head, char* word, int n_op, int code_bin) {
  // ADD element on top of the linked list
  Dicio_Instru_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Dicio_Instru_t));
  current->next->word = word;
  current->next->n_op = n_op;
  current->next->code_bin = code_bin;
  current->next->next = NULL;
}

Dicio_Instru_t * new_Dicio_Instru() {
  // Create a new struvture of type Dicio_Instru_t
  Dicio_Instru_t *head = NULL;
  head = malloc(sizeof(Dicio_Instru_t));
  head->word = "HEAD";
  head->n_op = -1;
  head->code_bin = -1;
  head->next = NULL;

  //ADD INSTRUCTIONS HERE
  push_Dicio_Instru(head, "ADD", 3, 100001);
  push_Dicio_Instru(head, "MOV", 2, 100001);
  push_Dicio_Instru(head, "MOVS", 1, 100001);

  return head;
}
