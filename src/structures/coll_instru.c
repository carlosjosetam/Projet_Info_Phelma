#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coll_instru.h"
#include "table_registers.h"

void print_Coll_INSTRU(Coll_INSTRU_t * head) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return;
  }

  Coll_INSTRU_t * current = head->next;

  printf("\nCOLLECTION INSTRUCTIONS ==>>\n");

  while (current != NULL) {
    if (current->n_op == 1) {
      printf("%2d | 0x%08X | %s %s (%d) | type: %d\n", current->ligne, current->decalage, current->instruction, current->op1, current->value_int_op1, current->type_op1);
    }
    else if (current->n_op == 2) {
      printf("%2d | 0x%08X | %s %s (%d), %s (%d) | ts: %d, %d\n", current->ligne, current->decalage, current->instruction, current->op1, current->value_int_op1, current->op2, current->value_int_op2, current->type_op1, current->type_op2);
    }
    else {
      printf("%2d | 0x%08X | %s %s (%d), %s (%d), %s (%d) | types: %d, %d, %d\n", current->ligne, current->decalage, current->instruction, current->op1, current->value_int_op1, current->op2, current->value_int_op2, current->op3, current->value_int_op3, current->type_op1, current->type_op2, current->type_op3);
    }
    current = current->next;
  }
  printf("\n");
}

void print_Coll_INSTRU_with_code(Coll_INSTRU_t * head) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return;
  }

  Coll_INSTRU_t * current = head->next;

  printf("\nCOLLECTION INSTRUCTIONS + BINARY CODE ==>>\n");

  while (current != NULL) {
    if (current->n_op == 1) {
      printf("%2d | 0x%08X | 0x%08X | %s %s (%d)\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction, current->op1, current->value_int_op1);
    }
    else if (current->n_op == 2) {
      printf("%2d | 0x%08X | 0x%08X | %s %s (%d), %s (%d)\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction, current->op1, current->value_int_op1, current->op2, current->value_int_op2);
    }
    else {
      printf("%2d | 0x%08X | 0x%08X | %s %s (%d), %s (%d), %s (%d)\n", current->ligne, current->decalage, current->code_binaire_instru, current->instruction, current->op1, current->value_int_op1, current->op2, current->value_int_op2, current->op3, current->value_int_op3);
    }
    current = current->next;
  }
  printf("\n");
}


void push_Coll_INSTRU(Coll_INSTRU_t * head, char * instruction, int n_op, int ligne, int decalage, char * op1, char * op2, char * op3, int type_op1, int type_op2, int type_op3) {
  /* ADD element on top of the linked list */
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
  current->next->value_int_op1 = 0;
  current->next->value_int_op2 = 0;
  current->next->value_int_op3 = 0;
  current->next->next = NULL;
  current->code_binaire_instru = 0;
}

Coll_INSTRU_t * new_Coll_INSTRU() {
  /* Create a new struvture of type Coll_INSTRU_t */
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

void put_operand_value_int(Coll_INSTRU_t * instruction, int index, int value) {
  if (index == 1) {
    instruction->value_int_op1 = value;
  }
  if (index == 2) {
    instruction->value_int_op2 = value;
  }
  if (index == 3) {
    instruction->value_int_op3 = value;
  }
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

int get_base_from_base_offset(Coll_INSTRU_t * instruction) {
  char * base_offset = NULL;
  char registre[5];

  Registers_t * table_registers = new_Registers();
  if (instruction->type_op1 == 18) base_offset = instruction->op1;
  if (instruction->type_op2 == 18) base_offset = instruction->op2;
  if (instruction->type_op3 == 18) base_offset = instruction->op3;

  if (base_offset == NULL) {
    return 0;
  }

  int i = 0;
  int j = 0;
  for (i; i<strlen(base_offset); i++) {
    if (base_offset[i] == '(') {
      i++;
      while (base_offset[i] != ')') {
        registre[j] = base_offset[i];
        j++; i++;
      }
      registre[j] = '\0';
      return get_number_Reg_in_table(table_registers, registre);
    }
  }
}

int get_offset_from_base_offset(Coll_INSTRU_t * instruction) {
  char * base_offset = NULL;
  char offset[32];

  if (instruction->type_op1 == 18) base_offset = instruction->op1;
  if (instruction->type_op2 == 18) base_offset = instruction->op2;
  if (instruction->type_op3 == 18) base_offset = instruction->op3;

  if (base_offset == NULL) {
    return 0;
  }


  int i = 0;
  int j = 0;
  for (i; i<strlen(base_offset); i++) {
    while (base_offset[i] != '(') {
        offset[j] = base_offset[i];
        j++; i++;
    }
    offset[j] = '\0';
    return hex2int(offset);
    }
}

int get_value_operand(Coll_INSTRU_t * instruction, int index) {
  if (index == 1) return instruction->value_int_op1;
  if (index == 2) return instruction->value_int_op2;
  if (index == 3) return instruction->value_int_op3;

  ERROR_MSG("Invalid index for get_operand");
}

int get_type_operand(Coll_INSTRU_t * instruction, int index) {
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
  /* If WORD is on list return true */
  /* Else, return false */

  Coll_INSTRU_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (line == current->ligne) {
      return current->decalage;
    }
  }
  return -1;
}

void push_code_binaire_instru(Coll_INSTRU_t * instru, code_binaire_instru) {
  instru->code_binaire_instru = code_binaire_instru;
}

bool relocate_symbole(Coll_INSTRU_t * head, int address_instru, char * symbole, int new_address) {
  Coll_INSTRU_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (address_instru == current->decalage) {
      if (strcmp(current->op1, symbole) == 0) current->value_int_op1 = new_address;
      else if (strcmp(current->op2, symbole) == 0) current->value_int_op2 = new_address;
      else if (strcmp(current->op3, symbole) == 0) current->value_int_op3 = new_address;
      else ERROR_MSG("ABORT. ERROR OF RELOCATION. Element on list_relocation but not found on coll_instru");
      return true;
    }
  }
  return false;
}
