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


Relocation_t * analyse_relocation_text(Coll_INSTRU_t * head_coll_instru, Etiquette_t * list_etiquettes) {
  Relocation_t * list_relocation = new_Relocation();
  Coll_INSTRU_t * current = head_coll_instru;

  char * section = NULL;
  int address_etiquette = -1;
  int address_instru = -1;
  Etiquette_t * etiquette = NULL;

  if (next_instru(current) == NULL) { //EXIT, NO .text TERMS
    return list_relocation;
  }

  while (next_instru(current) != NULL) {
    current = next_instru(current);

    /* if there's no operand i, we have NULL */
    for (int i = 1; i <= 3; i++) {
      if (get_type_operand(current, i) == 1) { /* IF WE HAVE SYMBOLE */
        etiquette = is_in_list_current(list_etiquettes, get_operand(current, i));
        if (etiquette != NULL) {
          section = get_section_etiquette(etiquette);
          address_etiquette = get_address_etiquette(etiquette);
          address_instru = get_address_instru(current);

          push_Relocation(list_relocation, address_instru, address_etiquette, section, "TESTE", get_operand(current, i));
        }
        else {
          push_Relocation(list_relocation, address_instru, address_etiquette, section, "TESTE", get_operand(current, i));
        }
      }
    }
   }

  return list_relocation;
}

//  Relocation_t * analyse_relocation_data(Coll_DATA_t * head_coll_data, Etiquette_t * list_etiquettes) {
//   Relocation_t * list_relocation = new_Relocation();
//   Coll_DATA_t * current = head_coll_data;
//
//   char * section = NULL;
//   int address_etiquette = -1;
//   int address_directive = -1;
//   Etiquette_t * etiquette = NULL;
//
//   if (next_instru(current) == NULL) { //EXIT, NO .text TERMS
//     return list_relocation;
//   }
//
//   while (next_instru(current) != NULL) {
//     current = next_instru(current);
//
//     /* if there's no operand i, we have NULL */
//     for (int i = 1; i <= 3; i++) {
//       if (get_type_operand(current, i) == 1) { /* IF WE HAVE SYMBOLE */
//         etiquette = is_in_list_current(list_etiquettes, get_operand(current, i));
//         if (etiquette != NULL) {
//           section = get_section_etiquette(etiquette);
//           address_etiquette = get_address_etiquette(etiquette);
//           address_instru = get_address_instru(current);
//
//           push_Relocation(list_relocation, address_instru, address_etiquette, section, "TESTE", get_operand(current, i));
//         }
//         else {
//           push_Relocation(list_relocation, address_instru, address_etiquette, section, "TESTE", get_operand(current, i));
//         }
//       }
//     }
//    }
//
//   return list_relocation;
// }
