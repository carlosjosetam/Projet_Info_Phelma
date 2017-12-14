#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coll_data.h"

void print_Coll_DATA(Coll_DATA_t * head) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return;
  }

  Coll_DATA_t * current = head->next;

  printf("\nCOLLECTION DATA ==>>\n");

  while (current != NULL) {
    printf("%2d | 0x%08X | %s %s | type: %d\n", current->ligne, current->decalage, current->directive, current->valeur, current->type);
    current = current->next;
  }
  printf("\n");
}

void print_Coll_DATA_with_code(Coll_DATA_t * head) {
  /* Print all elements on list */
  if (head->next == NULL) {
    return;
  }

  Coll_DATA_t * current = head->next;

  printf("\nCOLLECTION DATA ==>>\n");

  while (current != NULL) {
    printf("%2d | 0x%08X | 0x%08X | %s %s | type: %d\n", current->ligne, current->decalage, current->code_binaire, current->directive, current->valeur, current->type);
    current = current->next;
  }
  printf("\n");
}

int get_max_lines_data(Coll_DATA_t * head) {
  Coll_DATA_t * current = head;
  int max_line = 0;

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


void push_Coll_DATA(Coll_DATA_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur, int type) {
  /* ADD element on top of the linked list */
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
  current->next->type = type;
  current->next->next = NULL;
  current->next->code_binaire = 0;
}

void push_code_binaire_data(Coll_DATA_t * directive, int code_binaire) {
  directive->code_binaire = code_binaire;
}

Coll_DATA_t * new_Coll_DATA() {
  /* Create a new struvture of type Coll_DATA_t */
  Coll_DATA_t *head = NULL;
  head = malloc(sizeof(Coll_DATA_t));
  head->directive = "HEAD";
  head->n_op = -1;
  head->ligne = -1;
  head->decalage = -1;
  head->valeur = NULL;
  head->type = -1;
  head->next = NULL;

  return head;
}

int get_address_by_line_data(Coll_DATA_t * head, int line) {
  /* If WORD is on list return true */
  /* Else, return false */

  Coll_DATA_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (line == current->ligne) {
      return current->decalage;
    }
  }
  return -1;
}


int get_type_operand_directive(Coll_DATA_t * directive) {
  return directive->type;
}

int get_address_directive(Coll_DATA_t * directive) {
  return directive->decalage;
}

Coll_DATA_t * get_next_directive(Coll_DATA_t * directive) {
  return directive->next;
}

char * get_operand_directive(Coll_DATA_t * directive) {
  return directive->valeur;
}

int get_value_int_operand_directive(Coll_DATA_t * directive) {
  int type_operand = get_type_operand_directive(directive);
  char * operand = get_operand_directive(directive);

  int value = 0;
  if (type_operand == 6) { /* HEXA */
    value = hex2int(operand);
    DEBUG_MSG("operando HEXA %s, %d\n", operand, value);
  }
  if (type_operand == 2) {
    value = atoi(operand);
    DEBUG_MSG("operando DECIMAL %s, %d\n", operand, value);
  }
  if (type_operand == 5) {
    value = 0;
    DEBUG_MSG("operando ZERO %s, %d\n", operand, value);
  }
  if (type_operand == 7) { /* OCTA */
    value = octa2int(operand);
    DEBUG_MSG("operando OCTA %s, %d\n", operand, value);
  }
  if (type_operand == 1) {
    WARNING_MSG("operand => %s <= not relocated. Value replaced by 0", operand);
  }

  return value;
}

int get_line_directive(Coll_DATA_t * directive) {
  return directive->ligne;
}
