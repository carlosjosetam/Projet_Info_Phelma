#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_lexeme.h"

void print_list(Lexeme_t * head) {
  // Print all elements on list
  Lexeme_t * current = head->next;

  printf("\nLIST ==>>\n");

  while (current != NULL) {
    printf("%s %d | ligne: %d\n", current->word, current->type, current->ligne);
    current = current->next;
  }

  printf("\n");
}

void push(Lexeme_t * head, char* word, int type, int ligne) {
  // ADD element on top of the linked list
  Lexeme_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Lexeme_t));
  current->next->word = word;
  current->next->type = type;
  current->next->ligne = ligne;
  current->next->next = NULL;
}

int pop_last(Lexeme_t * head, char ** word) {
  // This function pops the LAST element of the linked list
  // returns its atributte TYPE and writes on the adress
  // WORD the atributte WORD
  Lexeme_t * current = head;

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
  int type = current->next->type;
  free(current->next);
  current->next = NULL;
  return type;
}

int pop_first(Lexeme_t * head, char ** word) {
  // This function pops the FIRST element of the linked list
  // returns its atributte TYPE and writes on the adress
  // WORD the atributte WORD
  Lexeme_t * current = head;
  if (current->next == NULL) {
    printf("Attention! List EMPTY! => ");
    printf("ABORT\n");
    printf("Verify your code and try again!\n");
    //abort();
    return -1;
  }

  *word = current->next->word;
  int type = current->next->type;
  Lexeme_t * aux = current->next;
  head->next = head->next->next;
  free(aux);
  return type;
}

bool is_empty(Lexeme_t * head) {
  // Verify if the list is EMPTY
  if (head->next == NULL) return true;
  return false;
}

Lexeme_t * new_lexeme() {
  // Create a new struvture of type Lexeme_t
  // and inicializes the head with HEAD 0
  Lexeme_t *head = NULL;
  head = malloc(sizeof(Lexeme_t));
  head->word = "HEAD";
  head->type = 0;
  head->ligne = -1;
  head->next = NULL;
  return head;
}

Lexeme_t * next_lexeme(Lexeme_t * head) {
  return head->next;
}

int type_lexeme(Lexeme_t * head) {
  return head->type;
}

char * word_lexeme(Lexeme_t * head) {
  return strdup(head->word);
}

int ligne_lexeme(Lexeme_t * head) {
  return head->ligne;
}

void effacer_2(Lexeme_t * before) {
  Lexeme_t * first = before->next;
  Lexeme_t * second = before->next;

  before->next = before->next->next->next;
  // free(first);
  // free(second); SEE THAT
}
