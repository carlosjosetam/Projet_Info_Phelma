#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dicio_directives.h"
#include "../global.h"

void print_Dicio_Directives(Dicio_Directives_t * head) {
  // Print all elements on list
  Dicio_Directives_t * current = head->next;
  type_directive_t * type;

  printf("\nDICIONAIRE DE DIRECTIVES ==>>\n");

  while (current->next != NULL) {
    printf("%s | n_op: %d | type_permit: %d\n", current->word, current->n_op, current->type_test->type);
    current = current->next;
  }
  printf("\n");
}

bool is_Dir_in_Dicio_Directives(Dicio_Directives_t * head, char * word) {
  // If WORD is on list return true
  // Else, return false

  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}

int type_permit_directive(Dicio_Directives_t * head, char * word) {
  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->type_permit;
    }
  }
  return -1;
}

bool is_type_permit_directive(Dicio_Directives_t * head, char * word, int type) {
  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      if (type == current->type_permit || type == current->type_permit_2 || type == current->type_permit_3) {
        return true;
      }
    }
  }
  return false;
}

bool is_value_permit_directive(Dicio_Directives_t * head, char * word, int type, char * value) {
  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      if (type == current->type_permit || type == current->type_permit_2 || type == current->type_permit_3) {
        if (type == 2) {
          if (is_in_interval_DECIMAL(atoi(value), atoi(current->type_test->max_value), atoi(current->type_test->min_value))) {
            if (is_in_interval_HEXA("0xff", "0xff", "0x22")) printf("TRUE");
            return true;
          }
        }
        if (type == 6) { // HEXA
          if (is_in_interval_HEXA(value, current->type_test->max_value, current->type_test->min_value)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool is_in_interval_DECIMAL(int cmp, int max_value, int min_value) {
  if (cmp <= max_value) {
    if (cmp >= min_value) {
      return true;
    }
  }
  return false;
}

bool is_in_interval_HEXA(char * cmp, char * max_value, char * min_value) { // Verfifies by size
  int cmp_hex = hex2int(cmp);
  int max_value_hex = hex2int(max_value);
  int min_value_hex = hex2int(min_value);
  if (cmp_hex <= max_value_hex) {
    if (cmp_hex >= min_value_hex) {
      return true;
    }
  }
  return false;
}

void push_Dicio_Directives(Dicio_Directives_t * head, char* word, int n_op, int type_permit, int type_permit_2, int type_permit_3, type_directive_t * type_test) {
  // ADD element on top of the linked list
  Dicio_Directives_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Dicio_Directives_t));
  current->next->word = word;
  current->next->n_op = n_op;
  current->next->type_permit = type_permit;
  current->next->type_permit_2 = type_permit_2;
  current->next->type_permit_3 = type_permit_3;
  current->type_test = type_test;
  current->next->next = NULL;
}

type_directive_t * new_Type_Directive(int type, char * max_value, char * min_value) {
  type_directive_t * head = malloc(sizeof(type_directive_t));

  head->type = type;
  head->max_value = max_value;
  head->min_value = min_value;

  return head;
}

Dicio_Directives_t * new_Dicio_Directives() {
  // Create a new struvture of type Dicio_Directives_t
  Dicio_Directives_t * head = NULL;
  head = malloc(sizeof(Dicio_Directives_t));
  head->word = "HEAD";
  head->n_op = -1;
  head->type_permit = -1;
  head->type_permit_2 = -1;
  head->type_permit_3 = -1;
  head->next = NULL;

  //ADD INSTRUCTIONS HERE
  push_Dicio_Directives(head, ".space", 1, 2, -1, -1, new_Type_Directive(2, "127", "-128")); // DECIMAL ONLY
  push_Dicio_Directives(head, ".byte", 1, 2, 6, -1, new_Type_Directive(2, "127", "-128")); // DECIMAL AND HEXA
  push_Dicio_Directives(head, ".word", 1, 2, 6, 1, new_Type_Directive(2, "127", "-128")); // DECIMAL AND HEXA AND SYMBOLE
  push_Dicio_Directives(head, ".asciiz", 1, 15, -1, -1, new_Type_Directive(2, "127", "-128")); // DECIMAL AND HEXA AND SYMBOLE

  push_Dicio_Directives(head, ".trashhhh", 1, 15, -1, -1, new_Type_Directive(2, "127", "-128")); // DECIMAL AND HEXA AND SYMBOLE

  return head;
}
