#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table_registers.h"

void print_Registers(Registers_t * head) {
  // Print all elements on list
  Registers_t * current = head->next;

  printf("\nTABLE DE REGISTERS ==>>\n");

  while (current != NULL) {
    printf("%s | %d\n", current->word, current->number);
    current = current->next;
  }
  printf("\n");
}

bool is_Reg_in_table(Registers_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false
  Registers_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}

unsigned char get_number_Reg_in_table(Registers_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false
  Registers_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->number;
    }
  }
  return -1;
}

void push_Registers(Registers_t * head, char * word, unsigned char number) {
  // ADD element on top of the linked list
  Registers_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Registers_t));
  current->next->word = word;
  current->next->number = number;
  current->next->next = NULL;
}

Registers_t * new_Registers() {
  // Create a new struvture of type Registers_t
  Registers_t *head = NULL;
  head = malloc(sizeof(Registers_t));
  head->word = "HEAD";
  head->number = -1;
  head->next = NULL;

  push_Registers(head, "$zero", 0);
  push_Registers(head, "$0", 0);
  push_Registers(head, "$1", 1);
  push_Registers(head, "$2", 2);
  push_Registers(head, "$3", 3);
  push_Registers(head, "$4", 4);
  push_Registers(head, "$5", 5);
  push_Registers(head, "$6", 6);
  push_Registers(head, "$7", 7);

  return head;
}
