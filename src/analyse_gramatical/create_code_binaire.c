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
    printf("Working on %s\n", instruction);
    bin = 0;
    cmpt_operands = 1;

    int i = 1;
    for(i; i <= 8; i++) {
      section = get_section_bin(dicio_instru, instruction, i);
      printf("%s\n", section);

      /* CASE SPECIAL */
      if (section == NULL) break;

      if (strcmp(section, "SPECIAL") == 0) {
        bin = bin << 6; /* decale de 6 with zeros 000000 */
        showbits(bin);

      }

      /* CASE OPERANDS REGISTER */
      if (strcmp(section, "rs") == 0) {
        bin = bin << 5 | get_value_operand(current, cmpt_operands);
        printf("operand: %d\n", get_value_operand(current, cmpt_operands));
        cmpt_operands++;
        showbits(bin);
      }
      if (strcmp(section, "rt") == 0) {
        bin = bin << 5 | get_value_operand(current, cmpt_operands);
        cmpt_operands++;
        showbits(bin);
      }
      if (strcmp(section, "rd") == 0) {
        bin = bin << 5 | get_value_operand(current, cmpt_operands);
        cmpt_operands++;
        showbits(bin);
      }

      /* CASE ZEROS */
      if (strcmp(section, "5zero") == 0) {
        bin = bin << 5;
        showbits(bin);
      }

      /* CASE INSTRU */
      if (strcmp(section, "INSTRU") == 0) {
        bin = bin << 6 | get_code_instru_bin(dicio_instru, instruction);
      }

    }

    showbits(bin);

    break;

  }
}
