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

bool is_Dir_in_Dicio_Directives(Dicio_Directives_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false

  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}

int type_permit_directive(Dicio_Directives_t * head, char * word) {
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

bool is_type_permit_directive(Dicio_Directives_t * head, char * word, int type) {
  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      if (type == current->type_permit || type == current->type_permit_2 || type == current->type_permit_3) {
        return true;
      }
    }
  }
  return false;
}

void push_Dicio_Directives(Dicio_Directives_t * head, char* word, int n_op, int type_permit, int type_permit_2, int type_permit_3) {
  // ADD element on top of the linked list
  Dicio_Directives_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Dicio_Directives_t));
  current->next->word = word;
  current->next->n_op = n_op;
  current->next->type_permit = type_permit;
  current->next->type_permit_2 = type_permit_2;
  current->next->type_permit_3 = type_permit_3;
  current->next->next = NULL;
}

Dicio_Directives_t * new_Dicio_Directives() {
  // Create a new struvture of type Dicio_Directives_t
  Dicio_Directives_t *head = NULL;
  head = malloc(sizeof(Dicio_Directives_t));
  head->word = "HEAD";
  head->n_op = -1;
  head->type_permit = -1;
  head->type_permit_2 = -1;
  head->type_permit_3 = -1;
  head->next = NULL;

  //ADD INSTRUCTIONS HERE
  push_Dicio_Directives(head, ".space", 1, 2, -1, -1); // DECIMAL ONLY
  push_Dicio_Directives(head, ".byte", 1, 2, 6, -1); // DECIMAL AND HEXA
  push_Dicio_Directives(head, ".word", 1, 2, 6, 1); // DECIMAL AND HEXA AND SYMBOLE
  push_Dicio_Directives(head, ".asciiz", 1, 15, -1, -1); // DECIMAL AND HEXA AND SYMBOLE

  return head;
}
