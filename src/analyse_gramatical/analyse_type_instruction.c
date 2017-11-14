#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/list_lexeme.h"
#include "../structures/coll_instru.h"
#include "../structures/dicio_instru.h"
#include "analyse_text.h"
#include "../../include/notify.h"

enum {START_TYPE_INSTRU};

void check_operand(char * addressing_type, int type_operand, int line, char * name_instruction, char * operand, int index) {

  // REGISTER DIRECT
  if (strcmp(addressing_type, "REG") == 0) { // CHECK IF ITS REGISTER
    if (type_operand == 9) { // REGISTER
      printf("OP%d REG %s of %s valide\n", index, operand, name_instruction);
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be REGISTER DIRECT", line, index, operand, name_instruction);
    }
  }

  // IMMEDIATE
  if (strcmp(addressing_type, "IME") == 0) {
    if (1 <= type_operand <= 2 || 5 <= type_operand <= 7) { // SYMBOLE DECIMAL ZERO HEXA OCTA
      printf("OP%d IME %s of %s valide\n", index, operand, name_instruction);
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be IMMEDIATE", line, index, operand, name_instruction);
    }
  }

  // BASE OFFSET
  if (strcmp(addressing_type, "OFF") == 0) {
    if (type_operand == 18) {
      printf("OP%d OFF %s of %s valide\n", index, operand, name_instruction);
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be BASE OFFSET", line, index, operand, name_instruction);
    }
  }

  // SHIFT ADDRESS
  // IMEDIATE 5BITS
  if (strcmp(addressing_type, "SA") == 0) {
    if (1 <= type_operand <= 2 || 5 <= type_operand <= 7) { // SYMBOLE DECIMAL ZERO HEXA OCTA
      printf("OP%d IME %s of %s valide\n", index, operand, name_instruction);
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be SHIFT ADDRESS", line, index, operand, name_instruction);
    }
  }

  // TARGET
  if (strcmp(addressing_type, "TAR") == 0) {
    ERROR_MSG("Type TAR is not yet accepted");
  }
}


void analyse_type_instruction(Coll_INSTRU_t * head_coll_instru, Dicio_Instru_t * dicionaire) {
  Coll_INSTRU_t * current = head_coll_instru;

  int S = START_TYPE_INSTRU;
  char * name_instruction = NULL;
  char * addressing_type = NULL;
  char * operand = NULL;
  int type_operand = -1;
  int line = -1;

  if (next_instru(current) == NULL) { //EXIT, NO .text TERMS
    return;
  }

  while (next_instru(current) != NULL) {
    current = next_instru(current);

    name_instruction = get_name_instruction(current);
    line = get_line(current);

    // VERIFICATION FIRST OPERAND
    operand = get_operand(current, 1);
    type_operand = get_type_operand(current, 1);
    addressing_type = get_addressing_type(dicionaire, name_instruction, 1); // get first addressing_type

    check_operand(addressing_type, type_operand, line, name_instruction, operand, 1);

    if (get_number_operands(current) != 1) { // TWO or More operands
      operand = get_operand(current, 2);
      type_operand = get_type_operand(current, 2);
      addressing_type = get_addressing_type(dicionaire, name_instruction, 2);

      check_operand(addressing_type, type_operand, line, name_instruction, operand, 2);
    }

    if (get_number_operands(current) == 3) { // Three operands
      operand = get_operand(current, 3);
      type_operand = get_type_operand(current, 3);
      addressing_type = get_addressing_type(dicionaire, name_instruction, 3);

      check_operand(addressing_type, type_operand, line, name_instruction, operand, 3);
    }

   }
  return;
}