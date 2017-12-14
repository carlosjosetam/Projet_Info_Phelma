#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coll_bss.h"

void print_Coll_BSS(Coll_BSS_t * head) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return;
  }

  Coll_BSS_t * current = head->next;

  printf("\nCOLLECTION BSS ==>>\n");

  while (current != NULL) {
    printf("%2d | 0x%02X | %s %s\n", current->ligne, current->decalage, current->directive, current->valeur);
    current = current->next;
  }
  printf("\n");
}


void push_Coll_BSS(Coll_BSS_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur) {
  /* ADD element on top of the linked list */
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
  current->next->code_binaire = 0;
}

Coll_BSS_t * new_Coll_BSS() {
  /* Create a new struvture of type Coll_BSS_t */
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

int get_max_lines_bss(Coll_BSS_t * head) {
  Coll_BSS_t * current = head;
  int max_line = 0;

  if (current->next == NULL) {
    max_line = current->ligne;
  }

  while (current->next != NULL) {
    if (max_line < current->ligne) {
      max_line = current->ligne;
    }
    current = current->next;
  }
  if (max_line < current->ligne) {
    max_line = current->ligne;
  }
  return max_line;
}

int get_address_by_line_bss(Coll_BSS_t * head, int line) {
  /* If WORD is on list return true */
  /* Else, return false */

  Coll_BSS_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (line == current->ligne) {
      return current->decalage;
    }
  }
  return -1;
}
