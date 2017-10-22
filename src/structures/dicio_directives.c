#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../global.h"
#include "dicio_directives.h"
#include "../../include/notify.h"


void print_Dicio_Directives(Dicio_Directives_t * head) {
  // Print all elements on list
  Dicio_Directives_t * current = head->next;
  type_directive_t * type;

  DEBUG_MSG("\nDICIONAIRE DE DIRECTIVES ==>>\n");

  while (current->next != NULL) {
    if (current->type_permit != NULL) {
      DEBUG_MSG("%s | n_op: %d | type_permit: %d", current->word, current->n_op, current->type_permit->type);
    }
    if (current->type_permit_2 != NULL) {
      printf(" | type_permit: %d", current->type_permit_2->type);
    }
    if (current->type_permit_3 != NULL) {
      printf(" | type_permit: %d", current->type_permit_3->type);
    }
    printf("\n");
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

bool is_type_permit_directive(Dicio_Directives_t * head, char * word, int type) {

  Dicio_Directives_t * current = head;
  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      if (current->type_permit != NULL) {
        if (type == current->type_permit->type) return true;
        else if (current->type_permit_2 != NULL) {
          if (type == current->type_permit_2->type) return true;
          else if (current->type_permit_3 != NULL) {
            if (type == current->type_permit_3->type) return true;
            else return false; // IF DIDN't MATCH ANY TYPE
          }
        }
      }
    }
  }
  return false;
}

bool is_value_permit_directive(Dicio_Directives_t * head, char * word, int type, char * value) {
  Dicio_Directives_t * current = head;
  type_directive_t * current_type;

  if (current->next == NULL) return false; // case EMPTY list
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      printf("HERE %d\n", type);

      if (current->type_permit != NULL) {
        if (type == current->type_permit->type) current_type = current->type_permit;
        else if (current->type_permit_2 != NULL) {
          if (type == current->type_permit_2->type) current_type = current->type_permit_2;
          else if (current->type_permit_3 != NULL) {
            if (type == current->type_permit_3->type) current_type = current->type_permit_3;
            else return false; // IF DIDN't MATCH ANY TYPE
          }
        }
      }

      // VERIFICATIONS
      if (current_type->type == 2) { // DECIMAL
        if (is_in_interval_DECIMAL(value, current_type->max_value, current_type->min_value)) return true;
      }
      if (current_type->type == 6) { // HEXA
        printf("HEXAAAAAAAAA ===== %s | %s\n", value, current_type->max_value);
        if (is_in_interval_HEXA(value, current_type->max_value, current_type->min_value)) return true;
      }
      if (current_type->type == 15) { // STRING
        return true;
      }
      if (current_type->type == 1) { // SYMBOLE
        return true;
      }
    }
  }
}

void push_Dicio_Directives(Dicio_Directives_t * head, char* word, int n_op, type_directive_t * type_permit, type_directive_t * type_permit_2, type_directive_t * type_permit_3) {
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
  current->next->next = NULL;
}

type_directive_t * Type_Directive(int type, char * max_value, char * min_value) {
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
  head->next = NULL;

  //ADD INSTRUCTIONS HERE
  // .space
  push_Dicio_Directives(head, ".space", 1, Type_Directive(2, "127", "-128"), NULL, NULL); // DECIMAL ONLY
  // .byte
  push_Dicio_Directives(head, ".byte", 1, Type_Directive(2, "127", "-128"), Type_Directive(6, "0xff", "0x0"), NULL); // DECIMAL AND HEXA
  // .word
  // 32 bits signed | HEXA | SYMBOLE 32 bits
  push_Dicio_Directives(head, ".word", 1, Type_Directive(2, "2147483647", "-2147483648"), Type_Directive(6, "0x7FFFFFFF", "0x0"), Type_Directive(1, "EMPTY", "EMPTY")); // DECIMAL AND HEXA AND SYMBOLE
  // .asciiz
  push_Dicio_Directives(head, ".asciiz", 1, Type_Directive(15, "EMPTY", "EMPTY"), NULL, NULL); // STRING

  //TRASH
  push_Dicio_Directives(head, "TRASH", -1, NULL, NULL, NULL);

  return head;
}
