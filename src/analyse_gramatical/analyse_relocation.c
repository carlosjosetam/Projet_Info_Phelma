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


Relocation_t * analyse_relocation_text(Coll_INSTRU_t * head_coll_instru, Etiquette_t * list_etiquettes) {
  Relocation_t * list_relocation = new_Relocation();
  Coll_INSTRU_t * current = head_coll_instru;

  char * section = NULL;
  int address_etiquette = -1;
  int address_instru = -1;
  Etiquette_t * etiquette = NULL;

  if (next_instru(current) == NULL) { /* EXIT, NO .text TERMS */
    return list_relocation;
  }

  while (next_instru(current) != NULL) {
    current = next_instru(current);

    /* if there's no operand i, we have NULL */
    int i = 1;
    for (i; i <= 3; i++) {
      if (get_type_operand(current, i) == 1) { /* IF WE HAVE SYMBOLE */
        etiquette = is_in_list_current(list_etiquettes, get_operand(current, i));
        if (etiquette != NULL) {
          section = get_section_etiquette(etiquette);
          address_etiquette = get_address_etiquette(etiquette);
          address_instru = get_address_instru(current);

          push_Relocation(list_relocation, address_instru, address_etiquette, section, "TESTE", get_operand(current, i));
        }
        else {
          address_instru = get_address_instru(current);
          push_Relocation(list_relocation, address_instru, 0, NULL, "[UNKNOWN]", get_operand(current, i));
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

        push_Relocation(list_relocation, address_directive, address_etiquette, section, "TESTE", get_operand_directive(current));
      }
      else {
        address_directive = get_address_directive(current);
        push_Relocation(list_relocation, address_directive, 0, NULL, "[UNKNOWN]", get_operand_directive(current));
        WARNING_MSG("line %d: SYMBOLE => %s <= not declared in this file", get_line_directive(current), get_operand_directive(current));
      }
    }
    }

  return list_relocation;
}
