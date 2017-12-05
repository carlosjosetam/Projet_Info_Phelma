#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dicio_instru.h"
#include "../../include/notify.h"
#include "../global.h"

void print_Dicio_Instru(Dicio_Instru_t * head) {
  /* Print all elements on list */
  Dicio_Instru_t * current = head->next;

  DEBUG_MSG("\nDICIONAIRE DE INSTRUCTIONS ==>>\n");

  while (current != NULL) {
    DEBUG_MSG("%s | %s | n_op: %d | %s | %s | %s | bin: %d\n", current->word, current->type, current->n_op, current->op1, current->op2, current->op3, current->code_bin);
    current = current->next;
  }
  DEBUG_MSG("\n");
}

int n_op_Dicio_Instru(Dicio_Instru_t * head, char * word) {
  /* If WORD is on list return true */
  /* Else, return false */


  Dicio_Instru_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->n_op;
    }
  }
  return -1;
}

bool is_Instru_Dicio_Instru(Dicio_Instru_t * head, char * word) {
  /* If WORD is on list return true */
  /* Else, return false */

  Dicio_Instru_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return true;
    }
  }
  return false;
}


void push_Dicio_Instru(Dicio_Instru_t * head, char * word, int n_op, char * type, char * op1, char * op2, char * op3, int code_bin) {
  /* ADD element on top of the linked list */
  Dicio_Instru_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(Dicio_Instru_t));
  current->next->word = word;
  current->next->n_op = n_op;
  current->next->type = type;
  current->next->op1 = op1;
  current->next->op2 = op2;
  current->next->op3 = op3;
  current->next->code_bin = code_bin;
  current->next->next = NULL;
}

Dicio_Instru_t * new_Dicio_Instru() {
  /* Create a new struvture of type Dicio_Instru_t */
  Dicio_Instru_t *head = NULL;
  head = malloc(sizeof(Dicio_Instru_t));
  head->word = "HEAD";
  head->n_op = -1;
  head->code_bin = -1;
  head->type = "NULL";
  head->op1 = "NULL";
  head->op2 = "NULL";
  head->op3 = "NULL";
  head->next = NULL;

  /*ADD INSTRUCTIONS HERE */
  push_Dicio_Instru(head, "ADD", 3, "R", "REG", "REG", "REG", 1111111);
  push_Dicio_Instru(head, "ADDI", 3, "I", "REG", "REG", "IME", 1111111);
  push_Dicio_Instru(head, "SUB", 3, "R", "REG", "REG", "REG", 1111111);
  push_Dicio_Instru(head, "LW", 2, "I", "REG", "OFF", NULL, 11111);
  push_Dicio_Instru(head, "BEQ", 3, "I", "REG", "REG", "OFF", 111111);
  push_Dicio_Instru(head, "MFHI", 1, "R", "REG", NULL, NULL, 111111);
  push_Dicio_Instru(head, "SLL", 3, "R", "REG", "REG", "SA", 111111);
  push_Dicio_Instru(head, "SLT", 3, "R", "REG", "REG", "REG", 1111111);
  push_Dicio_Instru(head, "BNE", 3, "J", "REG", "REG", "TAR", 1111111);
  push_Dicio_Instru(head, "J", 1, "J", "TAR", NULL, NULL, 1111111);




  /* PSEUDO INSTRUCTIONS */
  push_Dicio_Instru(head, "NOP", 0, NULL, NULL, NULL, NULL, 1111111);
  push_Dicio_Instru(head, "MOVE", 2, "R", "REG", "REG", NULL, 1111111);
  push_Dicio_Instru(head, "NEG", 2, "R", "REG", "REG", NULL, 1111111);
  push_Dicio_Instru(head, "LI", 2, "R", "REG", "IME", NULL, 1111111);
  push_Dicio_Instru(head, "BLT", 3, "J", "REG", "REG", "TAR", 1111111);



  push_Dicio_Instru(head, "NOP3", 3, "R", "REG", "REG", "REG", 100001);
  push_Dicio_Instru(head, "NOP2", 2, "R", "REG", "REG", NULL, 100001);
  push_Dicio_Instru(head, "NOP1", 1, "R", "REG", NULL, NULL, 100001);

  return head;
}

char * get_addressing_type(Dicio_Instru_t * dicionaire, char * word, int index) {
  Dicio_Instru_t * current = dicionaire;
  if (current->next == NULL) return NULL; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      if(index == 1) return current->op1;
      if(index == 2) return current->op2;
      if(index == 3) return current->op3;
    }
  }
  ERROR_MSG("Invalid index for get_addressing_type");
}
