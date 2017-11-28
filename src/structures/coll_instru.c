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
      printf("%2d | 0x%02X | %s %s | type: %d\n", current->ligne, current->decalage, current->instruction, current->op1, current->type_op1);
    }
    else if (current->n_op == 2) {
      printf("%2d | 0x%02X | %s %s, %s | types: %d, %d\n", current->ligne, current->decalage, current->instruction, current->op1, current->op2, current->type_op1, current->type_op2);
    }
    else {
      printf("%2d | 0x%02X | %s %s, %s, %s | types: %d, %d, %d\n", current->ligne, current->decalage, current->instruction, current->op1, current->op2, current->op3, current->type_op1, current->type_op2, current->type_op3);
    }
    current = current->next;
  }
  printf("\n");
}


void push_Coll_INSTRU(Coll_INSTRU_t * head, char * instruction, int n_op, int ligne, int decalage, char * op1, char * op2, char * op3, int type_op1, int type_op2, int type_op3) {
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
  current->next->type_op1 = type_op1;
  current->next->type_op2 = type_op2;
  current->next->type_op3 = type_op3;
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

int get_number_operands(Coll_INSTRU_t * instruction) {
  return instruction->n_op;
}

Coll_INSTRU_t * next_instru(Coll_INSTRU_t * instruction) {
  return instruction->next;
}

char * get_operand(Coll_INSTRU_t * instruction, int index) {
  if (index == 1) return instruction->op1;
  if (index == 2) return instruction->op2;
  if (index == 3) return instruction->op3;

  ERROR_MSG("Invalid index for get_operand");
}

int * get_type_operand(Coll_INSTRU_t * instruction, int index) {
  if (index == 1) return instruction->type_op1;
  if (index == 2) return instruction->type_op2;
  if (index == 3) return instruction->type_op3;

  ERROR_MSG("Invalid index for get_type_operand");
}

char * get_name_instruction(Coll_INSTRU_t * instruction) {
  return instruction->instruction;
}

int get_line(Coll_INSTRU_t * instruction) {
  return instruction->ligne;
}

int get_address_instru(Coll_INSTRU_t * instruction) {
  return instruction->decalage;
}

int get_address_by_line_text(Coll_INSTRU_t * head, int line) {
  // If WORD is on list return true
  // Else, return false

  Coll_INSTRU_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (line == current->ligne) {
      return current->decalage;
    }
  }
  return -1;
}
