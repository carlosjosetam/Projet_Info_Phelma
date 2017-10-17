#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_etiquette.h"

void print_list_etiquette(Etiquette_t * head) {
  // Print all elements on list
  Etiquette_t * current = head->next;

  printf("\nLIST DE ETIQUETTES ==>>\n");

  while (current != NULL) {
    printf("%s | ligne: %d\n", current->word, current->ligne);
    current = current->next;
  }

  printf("\n");
}

bool is_in_list(Etiquette_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false

  Etiquette_t * current = head;

  if (current->next == NULL) return false; // case EMPTY list

  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}

void push_etiquette(Etiquette_t * head, char* word, int ligne) {
  // ADD element on top of the linked list
  Etiquette_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Etiquette_t));
  current->next->word = word;
  current->next->ligne = ligne;
  current->next->next = NULL;
}

int pop_last_etiquette(Etiquette_t * head, char ** word) {
  // This function pops the LAST element of the linked list
  // returns its atributte LIGNE and writes on the adress
  // WORD the atributte WORD
  Etiquette_t * current = head;

  if (current->next == NULL) {
    printf("Attention! List EMPTY! => ");
    printf("ABORT\n");
    printf("Verify your code and try again!\n");
    abort();
    return -1;
  }

  while (current->next->next != NULL) {
    current = current->next;
  }

  *word = current->next->word;
  int ligne = current->next->ligne;
  free(current->next);
  current->next = NULL;
  return ligne;
}

int pop_first_etiquette(Etiquette_t * head, char ** word) {
  // This function pops the FIRST element of the linked list
  // returns its atributte LIGNE and writes on the adress
  // WORD the atributte WORD
  Etiquette_t * current = head;
  if (current->next == NULL) {
    printf("Attention! List EMPTY! => ");
    printf("ABORT\n");
    printf("Verify your code and try again!\n");
    //abort();
    return -1;
  }

  *word = current->next->word;
  int ligne = current->next->ligne;
  Etiquette_t * aux = current->next;
  head->next = head->next->next;
  free(aux);
  return ligne;
}

bool is_empty_etiquette(Etiquette_t * head) {
  // Verify if the list is EMPTY
  if (head->next == NULL) return true;
  return false;
}

Etiquette_t * new_etiquette() {
  // Create a new struvture of type Etiquette_t
  // and inicializes the head with HEAD -1
  Etiquette_t *head = NULL;
  head = malloc(sizeof(Etiquette_t));
  head->word = "HEAD";
  head->ligne = -1;
  head->next = NULL;
  return head;
}
