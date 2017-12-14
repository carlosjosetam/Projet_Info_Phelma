#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "../structures/list_lexeme.h"
#include "../structures/coll_instru.h"
#include "../structures/coll_data.h"
#include "../structures/dicio_instru.h"
#include "../structures/table_registers.h"
#include "analyse_text.h"
#include "../../include/notify.h"
#include "../structures/list_relocation.h"

char * get_type_relocation(char * instru) {
  if (strcmp_not_case_sensitive(instru, "LW")) return "R_MIPS_LO16";
  if (strcmp_not_case_sensitive(instru, "SW")) return "R_MIPS_LO16";

  if (strcmp_not_case_sensitive(instru, "LUI")) return "R_MIPS_HI16";

  if (strcmp_not_case_sensitive(instru, "J")) return "R_MIPS_26";
  if (strcmp_not_case_sensitive(instru, "JAL")) return "R_MIPS_26";

  return "[UNDEFINED]";
}
void message_relocation(int address_text, char * symbole, int new_address, char * section) {
  if (section == NULL) {
    printf("Relocation %s not done. Symbole not declared\n", symbole);
  }
  else {
    printf("Relocation 0x%08X -> %s -> %d\n", address_text, symbole, new_address);
  }
}

void relocation(Coll_INSTRU_t * head_coll_instru, Relocation_t * list_relocation) {
  Relocation_t * current_relocation = list_relocation;
  Coll_INSTRU_t * current = head_coll_instru;
  int address_etiquette = 0;
  int address_instru = 0;
  int new_address = 0;
  char * type_relocation = NULL;
  char * symbole = NULL;

  if (next_relocation(current_relocation) == NULL) {
    return;
  }

  while (next_relocation(current_relocation) != NULL) {
    current_relocation = next_relocation(current_relocation);
    address_etiquette = get_address_etiquette_from_list_relocation(current_relocation);
    address_instru = get_address_instru_from_list_relocation(current_relocation);
    symbole = get_symbole_from_list_relocation(current_relocation);
    type_relocation = get_type_relocation_from_list(current_relocation);

    if (get_section_from_list_relocation(current_relocation) == NULL) {
      message_relocation(address_instru, symbole, 0, NULL);
    }

    /* RELOCATION OF TYPE R_MIPS_26 */
    else if (strcmp(type_relocation, "R_MIPS_26") == 0) {
      if (address_etiquette % 4 == 0) { /* check if is divisible by 4 with no rest */
        new_address = address_etiquette/4;
        if (relocate_symbole(head_coll_instru, address_instru, symbole, new_address)) {
          message_relocation(address_instru, symbole, new_address, get_section_from_list_relocation(current_relocation));
        }
        else {
          ERROR_MSG("Error of relocation in function relocation in file analyse_relocation.c");
        }
      }
      else {
        ERROR_MSG("ERROR IN relocation. NUMBER NOT DIVISIBLE BY 4");
      }
    }

    /* RELOCATION OF TYPE R_MIPS_32 */
    else if (strcmp(type_relocation, "R_MIPS_32") == 0) {
      WARNING_MSG("RELOCATION OF TYPE R_MIPS_32 for symbole %s in address 0x%08X not available yet\n", symbole, address_instru);
    }

    /* RELOCATION OF TYPE R_MIPS_HI16 */
    else if (strcmp(type_relocation, "R_MIPS_HI16") == 0) {
      WARNING_MSG("RELOCATION OF TYPE R_MIPS_HI16 for symbole %s in address 0x%08X not available yet\n", symbole, address_instru);
    }

    /* RELOCATION OF TYPE R_MIPS_LO16 */
    else if (strcmp(type_relocation, "R_MIPS_LO16") == 0) {
      WARNING_MSG("RELOCATION OF TYPE R_MIPS_LO16 for symbole %s in address 0x%08X not available yet\n", symbole, address_instru);
    }

    /* CASE UNDEFINED */
    else if (strcmp(type_relocation, "UNDEFINED") == 0) {
      WARNING_MSG("TYPE OF RELOCATION NOT DEFINED for symbole %s in address 0x%08X\n", symbole, address_instru);
    }
  }

}

Relocation_t * analyse_relocation_text(Coll_INSTRU_t * head_coll_instru, Etiquette_t * list_etiquettes) {
  Relocation_t * list_relocation = new_Relocation();
  Coll_INSTRU_t * current = head_coll_instru;

  char * section = NULL;
  int address_etiquette = -1;
  int address_instru = -1;
  char * instru = NULL;
  Etiquette_t * etiquette = NULL;

  if (next_instru(current) == NULL) { /* EXIT, NO .text TERMS */
    return list_relocation;
  }

  while (next_instru(current) != NULL) {
    current = next_instru(current);
    instru = get_name_instruction(current);

    /* if there's no operand i, we have NULL */
    int i = 1;
    for (i; i <= 3; i++) {
      if (get_type_operand(current, i) == 1) { /* IF WE HAVE SYMBOLE */
        etiquette = is_in_list_current(list_etiquettes, get_operand(current, i));
        if (etiquette != NULL) {
          section = get_section_etiquette(etiquette);
          address_etiquette = get_address_etiquette(etiquette);
          address_instru = get_address_instru(current);

          push_Relocation(list_relocation, address_instru, address_etiquette, section, get_type_relocation(instru), get_operand(current, i));
        }
        else {
          address_instru = get_address_instru(current);
          push_Relocation(list_relocation, address_instru, 0, NULL, get_type_relocation(instru), get_operand(current, i));
          WARNING_MSG("line %d: SYMBOLE => %s <= not declared in this file", get_line(current), get_operand(current, i));
        }
      }
    }
   }

  return list_relocation;
}

 Relocation_t * analyse_relocation_data(Coll_DATA_t * head_coll_data, Etiquette_t * list_etiquettes) {
  Relocation_t * list_relocation = new_Relocation();
  Coll_DATA_t * current = head_coll_data;

  char * section = NULL;
  int address_etiquette = -1;
  int address_directive = -1;
  Etiquette_t * etiquette = NULL;

  if (get_next_directive(current) == NULL) { /* EXIT, NO .text TERMS */
    return list_relocation;
  }

  while (get_next_directive(current) != NULL) {
    current = get_next_directive(current);

    /* if there's no operand i, we have NULL */
    if (get_type_operand_directive(current) == 1) { /* IF WE HAVE SYMBOLE */
      etiquette = is_in_list_current(list_etiquettes, get_operand_directive(current));
      if (etiquette != NULL) {
        section = get_section_etiquette(etiquette);
        address_etiquette = get_address_etiquette(etiquette);
        address_directive = get_address_directive(current);

        push_Relocation(list_relocation, address_directive, address_etiquette, section, "R_MIPS_32", get_operand_directive(current));
      }
      else {
        address_directive = get_address_directive(current);
        push_Relocation(list_relocation, address_directive, 0, NULL, "[UNDEFINED]", get_operand_directive(current));
        WARNING_MSG("line %d: SYMBOLE => %s <= not declared in this file", get_line_directive(current), get_operand_directive(current));
      }
    }
    }

  return list_relocation;
}
