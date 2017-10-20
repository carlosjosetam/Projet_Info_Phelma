#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coll_bss.h"

void print_Coll_BSS(Coll_BSS_t * head) {
  // Print all elements on list
  Coll_BSS_t * current = head->next;

  printf("\nCOLLECTION BSS ==>>\n");

  while (current != NULL) {
    printf("%s | n_op: %d | ligne: %d | decalage: %d | valeur: %s\n", current->directive, current->n_op, current->ligne, current->decalage, current->valeur);
    current = current->next;
  }
  printf("\n");
}


void push_Coll_BSS(Coll_BSS_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur) {
  // ADD element on top of the linked list
  Coll_BSS_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Coll_BSS_t));
  current->next->directive = directive;
  current->next->n_op = n_op;
  current->next->ligne = ligne;
  current->next->decalage = decalage;
  current->next->valeur = valeur;
  current->next->next = NULL;
}

Coll_BSS_t * new_Coll_BSS() {
  // Create a new struvture of type Coll_BSS_t
  Coll_BSS_t *head = NULL;
  head = malloc(sizeof(Coll_BSS_t));
  head->directive = "HEAD";
  head->n_op = -1;
  head->ligne = -1;
  head->decalage = -1;
  head->valeur = NULL;
  head->next = NULL;

  return head;
}
