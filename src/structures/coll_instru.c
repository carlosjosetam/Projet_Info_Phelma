#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coll_instru.h"

void print_Coll_INSTRU(Coll_INSTRU_t * head) {
  // Print all elements on list
  Coll_INSTRU_t * current = head->next;

  printf("\nCOLLECTION INSTRUCTIONS ==>>\n");

  while (current != NULL) {
    if (current->n_op == 1) {
      printf("%s %s | ligne: %d | decalage: %d\n", current->instruction, current->op1, current->ligne, current->decalage);
    }
    else if (current->n_op == 2) {
      printf("%s %s, %s | ligne: %d | decalage: %d\n", current->instruction, current->op1, current->op2, current->ligne, current->decalage);
    }
    else {
      printf("%s %s, %s, %s | ligne: %d | decalage: %d\n", current->instruction, current->op1, current->op2, current->op3, current->ligne, current->decalage);
    }
    current = current->next;
  }
  printf("\n");
}


void push_Coll_INSTRU(Coll_INSTRU_t * head, char * instruction, int n_op, int ligne, int decalage, char * op1, char * op2, char * op3) {
  // ADD element on top of the linked list
  Coll_INSTRU_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Coll_INSTRU_t));
  current->next->instruction = instruction;
  current->next->n_op = n_op;
  current->next->ligne = ligne;
  current->next->decalage = decalage;
  current->next->op1 = op1;
  current->next->op2 = op2;
  current->next->op3 = op3;
  current->next->next = NULL;
}

Coll_INSTRU_t * new_Coll_INSTRU() {
  // Create a new struvture of type Coll_INSTRU_t
  Coll_INSTRU_t *head = NULL;
  head = malloc(sizeof(Coll_INSTRU_t));
  head->instruction = "HEAD";
  head->n_op = -1;
  head->ligne = -1;
  head->decalage = -1;
  head->op1 = NULL;
  head->op2 = NULL;
  head->op3 = NULL;
  head->next = NULL;

  return head;
}
