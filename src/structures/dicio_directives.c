#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dicio_directives.h"

void print_Dicio_Directives(Dicio_Directives_t * head) {
  // Print all elements on list
  Dicio_Directives_t * current = head->next;

  printf("\nDICIONAIRE DE DIRECTIVES ==>>\n");

  while (current != NULL) {
    printf("%s | n_op: %d | type_permit: %d\n", current->word, current->n_op, current->type_permit);
    current = current->next;
  }
  printf("\n");
}

int is_Dir_in_Dicio_Directives(Dicio_Directives_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false

  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->type_permit;
    }
  }
  return -1;
}

void push_Dicio_Directives(Dicio_Directives_t * head, char* word, int n_op, int type_permit) {
  // ADD element on top of the linked list
  Dicio_Directives_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Dicio_Directives_t));
  current->next->word = word;
  current->next->n_op = n_op;
  current->next->type_permit = type_permit;
  current->next->next = NULL;
}

Dicio_Directives_t * new_Dicio_Directives() {
  // Create a new struvture of type Dicio_Directives_t
  Dicio_Directives_t *head = NULL;
  head = malloc(sizeof(Dicio_Directives_t));
  head->word = "HEAD";
  head->n_op = -1;
  head->type_permit = -1;
  head->next = NULL;

  //ADD INSTRUCTIONS HERE
  push_Dicio_Directives(head, ".space", 1, 2); // DECIMAL

  return head;
}
