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
    printf("%s\n", current->bin->sec1);
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

char * get_section_bin(Dicio_Instru_t * head, char * word, int index) {
  /* If WORD is on list return true */
  /* Else, return false */

  Dicio_Instru_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      printf("found! index %d\n", index);
      if (index == 1) return current->bin->sec1;
      if (index == 2) return current->bin->sec2;
      if (index == 3) return current->bin->sec3;
      if (index == 4) return current->bin->sec4;
      if (index == 5) return current->bin->sec5;
      if (index == 6) return current->bin->sec6;
      if (index == 7) return current->bin->sec7;
      if (index == 8) return current->bin->sec8;
    }
  }
  ERROR_MSG("Section not found on get_section_bin");
  return NULL;
}

int get_code_instru_bin(Dicio_Instru_t * head, char * word) {
  /* If WORD is on list return true */
  /* Else, return false */

  Dicio_Instru_t * current = head;
  if (current->next == NULL) return false; /* case EMPTY list */
  while (current->next != NULL) {
    current = current->next;
    if (strcmp(strdup(word), strdup(current->word)) == 0) {
      return current->bin->code_binaire;
    }
  }
  ERROR_MSG("Section not found on get_section_bin");
  return -1;
}


void push_Dicio_Instru(Dicio_Instru_t * head, char * word, int n_op, char * type, char * op1, char * op2, char * op3, Binaire_t * bin) {
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
  current->next->bin = bin;
  current->next->next = NULL;
}

Binaire_t * new_Binaire(char n_sections, char code_binaire, char * sec1, char * sec2, char * sec3, char * sec4, char * sec5, char * sec6, char * sec7, char * sec8) {
  Binaire_t * head = NULL;

  head = malloc(sizeof(Binaire_t));
  head->n_sections = n_sections;
  head->code_binaire = code_binaire;
  head->sec1 = sec1;
  head->sec2 = sec2;
  head->sec3 = sec3;
  head->sec4 = sec4;
  head->sec5 = sec5;
  head->sec6 = sec6;
  head->sec7 = sec7;
  head->sec8 = sec8;

  return head;
}

Dicio_Instru_t * new_Dicio_Instru() {
  /* Create a new struvture of type Dicio_Instru_t */
  Dicio_Instru_t *head = NULL;
  head = malloc(sizeof(Dicio_Instru_t));
  head->word = "HEAD";
  head->n_op = -1;
  head->type = "NULL";
  head->op1 = "NULL";
  head->op2 = "NULL";
  head->op3 = "NULL";
  head->next = NULL;

  Binaire_t * bin = NULL;

  /*ADD INSTRUCTIONS HERE */
  bin = new_Binaire(6, 0b100000, "SPECIAL", "rs", "rt", "rd", "5zero", "INSTRU", NULL, NULL);
  push_Dicio_Instru(head, "ADD", 3, "R", "REG", "REG", "REG", bin);


  push_Dicio_Instru(head, "ADDI", 3, "I", "REG", "REG", "IME", bin);
  push_Dicio_Instru(head, "SUB", 3, "R", "REG", "REG", "REG", bin);
  push_Dicio_Instru(head, "LW", 2, "I", "REG", "OFF", NULL, bin);
  push_Dicio_Instru(head, "BEQ", 3, "I", "REG", "REG", "OFF", bin);
  push_Dicio_Instru(head, "MFHI", 1, "R", "REG", NULL, NULL, bin);
  push_Dicio_Instru(head, "SLL", 3, "R", "REG", "REG", "SA", bin);
  push_Dicio_Instru(head, "SLT", 3, "R", "REG", "REG", "REG", bin);
  push_Dicio_Instru(head, "BNE", 3, "J", "REG", "REG", "TAR", bin);
  push_Dicio_Instru(head, "J", 1, "J", "TAR", NULL, NULL, bin);




  /* PSEUDO INSTRUCTIONS */
  push_Dicio_Instru(head, "NOP", 0, NULL, NULL, NULL, NULL, bin);
  push_Dicio_Instru(head, "MOVE", 2, "R", "REG", "REG", NULL, bin);
  push_Dicio_Instru(head, "NEG", 2, "R", "REG", "REG", NULL, bin);
  push_Dicio_Instru(head, "LI", 2, "R", "REG", "IME", NULL, bin);
  push_Dicio_Instru(head, "BLT", 3, "J", "REG", "REG", "TAR", bin);



  push_Dicio_Instru(head, "NOP3", 3, "R", "REG", "REG", "REG", bin);
  push_Dicio_Instru(head, "NOP2", 2, "R", "REG", "REG", NULL, bin);
  push_Dicio_Instru(head, "NOP1", 1, "R", "REG", NULL, NULL, bin);

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
