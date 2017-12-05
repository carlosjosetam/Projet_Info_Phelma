#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table_registers.h"

void print_Registers(Registers_t * head) {
  /* Print all elements on list */
  Registers_t * current = head->next;

  DEBUG_MSG("\nTABLE DE REGISTERS ==>>\n");

  while (current != NULL) {
    DEBUG_MSG("%s | %d\n", current->word, current->number);
    current = current->next;
  }
  DEBUG_MSG("\n");
}

bool is_Reg_in_table(Registers_t * head, char * word) {
  /* If WORD is on list return true */
  /* Else, return false */
  Registers_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}

unsigned char get_number_Reg_in_table(Registers_t * head, char * word) {
  /* If WORD is on list return true */
  /* Else, return false */
  Registers_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->number;
    }
  }
  return 0;
}

void push_Registers(Registers_t * head, char * word, unsigned char number) {
  /* ADD element on top of the linked list */
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
  /* Create a new struvture of type Registers_t */
  Registers_t *head = NULL;
  head = malloc(sizeof(Registers_t));
  head->word = "HEAD";
  head->number = -1;
  head->next = NULL;

  push_Registers(head, "$zero", 0);
  push_Registers(head, "$0", 0);

  push_Registers(head, "$at", 1);
  push_Registers(head, "$1", 1);

  push_Registers(head, "$v0", 2);
  push_Registers(head, "$2", 2);

  push_Registers(head, "$v1", 3);
  push_Registers(head, "$3", 3);

  push_Registers(head, "$a0", 4);
  push_Registers(head, "$4", 4);

  push_Registers(head, "$a1", 5);
  push_Registers(head, "$5", 5);

  push_Registers(head, "$a2", 6);
  push_Registers(head, "$6", 6);

  push_Registers(head, "$a3", 7);
  push_Registers(head, "$7", 7);

  push_Registers(head, "$t0", 8);
  push_Registers(head, "$8", 8);

  push_Registers(head, "$t1", 9);
  push_Registers(head, "$9", 9);

  push_Registers(head, "$t2", 10);
  push_Registers(head, "$10", 10);

  push_Registers(head, "$t3", 11);
  push_Registers(head, "$11", 11);

  push_Registers(head, "$t4", 12);
  push_Registers(head, "$12", 12);

  push_Registers(head, "$t5", 13);
  push_Registers(head, "$13", 13);

  push_Registers(head, "$t6", 14);
  push_Registers(head, "$14", 14);

  push_Registers(head, "$t7", 15);
  push_Registers(head, "$15", 15);

  push_Registers(head, "$s0", 16);
  push_Registers(head, "$16", 16);

  push_Registers(head, "$s1", 17);
  push_Registers(head, "$17", 17);

  push_Registers(head, "$s2", 18);
  push_Registers(head, "$18", 18);

  push_Registers(head, "$s3", 19);
  push_Registers(head, "$19", 19);

  push_Registers(head, "$s4", 20);
  push_Registers(head, "$20", 20);

  push_Registers(head, "$s5", 21);
  push_Registers(head, "$21", 21);

  push_Registers(head, "$s6", 22);
  push_Registers(head, "$22", 22);

  push_Registers(head, "$s7", 23);
  push_Registers(head, "$23", 23);

  push_Registers(head, "$t8", 24);
  push_Registers(head, "$24", 24);

  push_Registers(head, "$t9", 25);
  push_Registers(head, "$25", 25);

  push_Registers(head, "$k0", 26);
  push_Registers(head, "$26", 26);

  push_Registers(head, "$k1", 27);
  push_Registers(head, "$27", 27);

  push_Registers(head, "$gp", 28);
  push_Registers(head, "$28", 28);

  push_Registers(head, "$sp", 29);
  push_Registers(head, "$29", 29);

  push_Registers(head, "$fp", 30);
  push_Registers(head, "$30", 30);

  push_Registers(head, "$ra", 31);
  push_Registers(head, "$31", 31);

  return head;
}
