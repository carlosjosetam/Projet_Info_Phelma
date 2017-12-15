#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../structures/list_lexeme.h"
#include "../structures/list_etiquette.h"
#include "../structures/list_relocation.h"
#include "etiquette.h"
#include "division_section.h"
#include "analyse_bss.h"
#include "analyse_data.h"
#include "analyse_text.h"
#include "analyse_gramatical_1.h"
#include "analyse_symboles.h"
#include "analyse_type_instruction.h"
#include "analyse_relocation.h"
#include "create_code_binaire.h"


void create_code_binaire_data(Coll_DATA_t * directives, Dicio_Directives_t * dicio_directives) {
  Coll_DATA_t * current = directives;
  if (get_next_directive(current) == NULL) { /* EXIT, NO .text TERMS */
    return;
  }


  while (get_next_directive(current) != NULL) {
    current = get_next_directive(current);
    push_code_binaire_data(current, get_value_int_operand_directive(current));
  }
}

void create_code_binaire(Coll_INSTRU_t * instructions, Dicio_Instru_t * dicio_instru) {
  Coll_INSTRU_t * current = instructions;
  if (next_instru(current) == NULL) { /* EXIT, NO .text TERMS */
    return;
  }

  int bin = 0;
  int cmpt_operands = 0;
  char * instruction;
  char * section;

  while (next_instru(current) != NULL) {
    current = next_instru(current);
    instruction = get_name_instruction(current);
    DEBUG_MSG("Working on %s\n", instruction);
    bin = 0;
    cmpt_operands = 1;

    int i = 1;
    for(i; i <= 8; i++) {
      section = get_section_bin(dicio_instru, instruction, i);
      DEBUG_MSG("%s\n", section);

      /* CASE SPECIAL */
      if (section == NULL) break;

      if (strcmp(section, "SPECIAL") == 0) {
        bin = bin << 6; /* decale de 6 with zeros 000000 */
      }


      /* CASE OPERANDS REGISTER */
      if (strcmp(section, "5op1") == 0) {
        bin = bin << 5 | get_value_operand(current, 1);
      }

      if (strcmp(section, "5op2") == 0) {
        bin = bin << 5 | get_value_operand(current, 2);
      }

      if (strcmp(section, "5op3") == 0) {
        bin = bin << 5 | get_value_operand(current, 3);
      }

      /* CASE IMEDIATE 16 bits */
      if (strcmp(section, "16op1") == 0) {
        int value_ime16 = get_value_operand(current, 1);
        if (value_ime16 < 0) {
          value_ime16 = 65536 + value_ime16;
        }

        bin = bin << 16 | value_ime16;
      }

      if (strcmp(section, "16op2") == 0) {
        int value_ime16 = get_value_operand(current, 2);
        if (value_ime16 < 0) {
          value_ime16 = 65536 + value_ime16;
        }

        bin = bin << 16 | value_ime16;
      }

      if (strcmp(section, "16op3") == 0) {
        int value_ime16 = get_value_operand(current, 3);
        if (value_ime16 < 0) {
          value_ime16 = 65536 + value_ime16;
        }

        bin = bin << 16 | value_ime16;
      }

      /* CASE instr_index TARGET */
      if (strcmp(section, "26op1") == 0) {
        bin = bin << 26 | get_value_operand(current, 1);
      }

      if (strcmp(section, "rs") == 0) {
        bin = bin << 5 | get_value_operand(current, cmpt_operands);
      }
      if (strcmp(section, "rt") == 0) {
        bin = bin << 5 | get_value_operand(current, cmpt_operands);
      }
      if (strcmp(section, "rd") == 0) {
        bin = bin << 5 | get_value_operand(current, cmpt_operands);
      }

      /* CASE ZEROS */
      if (strcmp(section, "5zero") == 0) {
        bin = bin << 5;
      }

      if (strcmp(section, "10zero") == 0) {
        bin = bin << 10;
      }

      if (strcmp(section, "20zero") == 0) {
        bin = bin << 10;
      }

      /* CASE INSTRU */
      if (strcmp(section, "INSTRU") == 0) {
        bin = bin << 6 | get_code_instru_bin(dicio_instru, instruction);
      }
      
      /* CASE BASE */
      if (strcmp(section, "base") == 0) {
        int base = get_base_from_base_offset(current);
        DEBUG_MSG("%d\n", base);
        bin = bin << 5 | base;
      }

      /* CASE OFFSET */
      if (strcmp(section, "offset") == 0) {
        int offset = get_offset_from_base_offset(current);
        DEBUG_MSG("%d\n", offset);
        bin = bin << 16 | offset;
      }

    }

    push_code_binaire_instru(current, bin);
    DEBUG_MSG("code ==>>");
    DEBUG_MSG("\n");



  }
}
