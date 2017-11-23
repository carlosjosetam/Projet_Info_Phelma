#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "../structures/list_lexeme.h"
#include "../structures/coll_instru.h"
#include "../structures/dicio_instru.h"
#include "../structures/table_registers.h"
#include "analyse_text.h"
#include "../../include/notify.h"
#include "../structures/list_relocation.h"

enum {START_TYPE_INSTRU};

bool check_value_operand(char * addressing_type, int type_operand, int line, char * name_instruction, char * operand, int index, Registers_t * table_registers) {
  //DECODER OPERANDS
  short value = 0;
  if (type_operand == 6) { // HEXA
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
  if (type_operand == 7) {
    ERROR_MSG("FUNCTION FOR VERIFYING OCTA VALUE NOT IMPLEMENTED YET");
  }

  // REGISTER DIRECT
  if (strcmp(addressing_type, "REG") == 0) { // CHECK IF ITS REGISTER
    if (is_Reg_in_table(table_registers, operand)) {
      DEBUG_MSG("Register %s valide\n", operand);
    }
    else {
      WARNING_MSG("line %d: Register => %s <= not alowed for this device", line, operand); return false;
    }
  }

  // IMMEDIATE
  if (strcmp(addressing_type, "IME") == 0) {
    if (type_operand == 1) { // If its SYMBOLE
      DEBUG_MSG("Symbole %s valide\n", operand);
      //faire choses
    }
    else { // HEXA, DECIMAL, OCTA, ZERO
      if (SHRT_MIN <= value <= SHRT_MAX) {
        DEBUG_MSG("Operand IMM %d valide\n", value);
      }
      else {
        WARNING_MSG("line %d: Value of operand => %s <= off-limits", line, operand); return false;
      }
    }
  }

  // BASE OFFSET
  if (strcmp(addressing_type, "OFF") == 0) {

  }

  // SHIFT ADDRESS
  // IMEDIATE 5BITS
  if (strcmp(addressing_type, "SA") == 0) {
    if (type_operand == 1) { // If its SYMBOLE
      DEBUG_MSG("Symbole %s valide\n", operand);
      //faire choses
    }
    else { // HEXA, DECIMAL, OCTA, ZERO
      if (0 <= value <= 31) {
        DEBUG_MSG("Operand SA %d valide\n", value);
      }
      else {
        WARNING_MSG("line %d: Value of operand => %s <= off-limits", line, operand); return false;
      }
    }

  }

  // TARGET
  if (strcmp(addressing_type, "TAR") == 0) {

  }

  return true;
}

bool check_operand(char * addressing_type, int type_operand, int line, char * name_instruction, char * operand, int index) {

  // REGISTER DIRECT
  if (strcmp(addressing_type, "REG") == 0) { // CHECK IF ITS REGISTER
    if (type_operand == 9) { // REGISTER
      DEBUG_MSG("OP%d REG %s of %s valide\n", index, operand, name_instruction);
      return true;
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be REGISTER DIRECT", line, index, operand, name_instruction);
      return false;
    }
  }

  // IMMEDIATE
  if (strcmp(addressing_type, "IME") == 0) {
    if (1 <= type_operand <= 2 || 5 <= type_operand <= 7) { // SYMBOLE DECIMAL ZERO HEXA OCTA
      DEBUG_MSG("OP%d IME %s of %s valide\n", index, operand, name_instruction);
      return true;
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be IMMEDIATE", line, index, operand, name_instruction);
      return false;
    }
  }

  // BASE OFFSET
  if (strcmp(addressing_type, "OFF") == 0) {
    if (type_operand == 18) {
      DEBUG_MSG("OP%d OFF %s of %s valide\n", index, operand, name_instruction);
      return true;
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be BASE OFFSET", line, index, operand, name_instruction);
      return false;
    }
  }

  // SHIFT ADDRESS
  // IMEDIATE 5BITS
  if (strcmp(addressing_type, "SA") == 0) {
    if (1 <= type_operand <= 2 || 5 <= type_operand <= 7) { // SYMBOLE DECIMAL ZERO HEXA OCTA
      DEBUG_MSG("OP%d IME %s of %s valide\n", index, operand, name_instruction);
      return true;
    }
    else {
      WARNING_MSG("line %d: Wrong operand %d => %s <= for => %s <= instruction. The addressing type should be SHIFT ADDRESS", line, index, operand, name_instruction);
      return false;
    }
  }

  // TARGET
  if (strcmp(addressing_type, "TAR") == 0) {
    ERROR_MSG("Type TAR is not yet accepted");
    return false;
  }
}


void analyse_type_instruction(Coll_INSTRU_t * head_coll_instru, Dicio_Instru_t * dicionaire) {
  Coll_INSTRU_t * current = head_coll_instru;

  Registers_t * table_registers = new_Registers();
  print_Registers(table_registers);

  if(is_Reg_in_table(table_registers, "$zero")){
    unsigned char number = get_number_Reg_in_table(table_registers, "$zero");
    DEBUG_MSG("ouiii %d\n", number);
  }

  int S = START_TYPE_INSTRU;
  char * name_instruction = NULL;
  char * addressing_type = NULL;
  char * operand = NULL;
  int type_operand = -1;
  int line = -1;
  bool erro = false;

  if (next_instru(current) == NULL) { //EXIT, NO .text TERMS
    return;
  }

  while (next_instru(current) != NULL) {
    current = next_instru(current);

    name_instruction = get_name_instruction(current);
    line = get_line(current);

    if (get_number_operands(current) != 0) {
      // VERIFICATION FIRST OPERAND
      operand = get_operand(current, 1);
      type_operand = get_type_operand(current, 1);
      addressing_type = get_addressing_type(dicionaire, name_instruction, 1); // get first addressing_type

      if (check_operand(addressing_type, type_operand, line, name_instruction, operand, 1)) {
          DEBUG_MSG("Verification de valeur\n");
          if (!check_value_operand(addressing_type, type_operand, line, name_instruction, operand, 2, table_registers)) {
            erro = true;
          }
      }
      else {
        erro = true;
        WARNING_MSG("line %d: Wrong type of operand. The program won't check it's value. please correct", line);
      }

      if (get_number_operands(current) != 1) { // TWO or More operands
        operand = get_operand(current, 2);
        type_operand = get_type_operand(current, 2);
        addressing_type = get_addressing_type(dicionaire, name_instruction, 2);

        if (check_operand(addressing_type, type_operand, line, name_instruction, operand, 2)) {
            DEBUG_MSG("Verification de valeur\n");
            if (!check_value_operand(addressing_type, type_operand, line, name_instruction, operand, 2, table_registers)) {
              erro = true;
            }
        }
        else {
          erro = true;
          WARNING_MSG("line %d: Wrong type of operand. The program won't check it's value. please correct", line);
        }
      }

      if (get_number_operands(current) == 3) { // Three operands
        operand = get_operand(current, 3);
        type_operand = get_type_operand(current, 3);
        addressing_type = get_addressing_type(dicionaire, name_instruction, 3);

        if (check_operand(addressing_type, type_operand, line, name_instruction, operand, 1)) {
            DEBUG_MSG("Verification de valeur\n");
            if (!check_value_operand(addressing_type, type_operand, line, name_instruction, operand, 3, table_registers)) {
              erro = true;
            }
        }
        else {
          erro = true;
          WARNING_MSG("line %d: Wrong type of operand. The program won't check it's value. please correct", line);
        }
      }
    }
   }
   if (erro) {
     ERROR_MSG("Correct instructions errors to continue");
   }
  return;
}
