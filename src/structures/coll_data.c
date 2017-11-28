#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coll_data.h"

void print_Coll_DATA(Coll_DATA_t * head) {
  // Print all elements on list
  Coll_DATA_t * current = head->next;

  printf("\nCOLLECTION DATA ==>>\n");

  while (current != NULL) {
    printf("%2d | 0x%02X | %s %s\n", current->ligne, current->decalage, current->directive, current->valeur);
    current = current->next;
  }
  printf("\n");
}


void push_Coll_DATA(Coll_DATA_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur) {
  // ADD element on top of the linked list
  Coll_DATA_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Coll_DATA_t));
  current->next->directive = directive;
  current->next->n_op = n_op;
  current->next->ligne = ligne;
  current->next->decalage = decalage;
  current->next->valeur = valeur;
  current->next->next = NULL;
}

Coll_DATA_t * new_Coll_DATA() {
  // Create a new struvture of type Coll_DATA_t
  Coll_DATA_t *head = NULL;
  head = malloc(sizeof(Coll_DATA_t));
  head->directive = "HEAD";
  head->n_op = -1;
  head->ligne = -1;
  head->decalage = -1;
  head->valeur = NULL;
  head->next = NULL;

  return head;
}

int get_address_by_line_data(Coll_DATA_t * head, int line) {
  // If WORD is on list return true
  // Else, return false

  Coll_DATA_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (line == current->ligne) {
      return current->decalage;
    }
  }
  return -1;
}
