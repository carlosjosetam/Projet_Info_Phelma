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


void analyse_gramatical_1(Lexeme_t * head_lexemes, Lexeme_t * head_text, Lexeme_t * head_data, Lexeme_t * head_bss, Etiquette_t * list_etiquettes, Dicio_Instru_t * dicio_instru, Dicio_Directives_t * dicio_directives) {

  print_list(head_lexemes);

  /* ANALYSE OF CERTAINS SYMBOLES */
  Lexeme_t * new_lexemes = analyse_symboles(head_lexemes);
  print_list(new_lexemes);

  /* DIVISION IN SECTIONS */
  division_section(new_lexemes, head_text, head_data, head_bss, dicio_instru);
  print_list(head_text);
  print_list(head_data);
  print_list(head_bss);

  /* SEARCH OF ETIQUETTES */
  DEBUG_MSG("\nANALYSE D'ETIQUETTES EN COURS...\n");
  cherche_etiquette(head_text, list_etiquettes, "text");
  cherche_etiquette(head_data, list_etiquettes, "data");
  cherche_etiquette(head_bss, list_etiquettes, "bss");

  DEBUG_MSG("LIST OF .TEXT\n");
  print_list(head_text);
  Coll_INSTRU_t * coll_instru = analyse_text(head_text, dicio_instru);
  /* print_Coll_INSTRU(coll_instru); */

  DEBUG_MSG("LIST OF .DATA\n");
  print_list(head_data);
  Coll_DATA_t * coll_data = analyse_data(head_data, dicio_directives);
  print_Coll_DATA(coll_data);

  DEBUG_MSG("LIST OF .BSS\n");
  print_list(head_bss);
  Coll_BSS_t * coll_bss = analyse_bss(head_bss, dicio_directives);
  print_Coll_BSS(coll_bss);

  /* REWRITE ADDRESS Etiquette */
  update_address_etiquettes(list_etiquettes, coll_bss, coll_instru, coll_data);
  print_list_etiquette(list_etiquettes);

  /* ANALYSE TYPE INSTRUCTIONS */
  analyse_type_instruction(coll_instru, dicio_instru);
  print_Coll_INSTRU(coll_instru);

  /* ANALYSE RELOCATION TEXT */
  Relocation_t * reloc_text = analyse_relocation_text(coll_instru, list_etiquettes);
  printf("\nLIST DE RELOCATION TEXT==>>\n");
  print_list_relocation(reloc_text);

  Relocation_t * reloc_data = analyse_relocation_data(coll_data, list_etiquettes);
  printf("\nLIST DE RELOCATION DATA==>>\n");
  print_list_relocation(reloc_data);

  /* RELOCATION */
  printf("RELOCATION IN PROCESS...\n");
  printf("FOR .text\n");
  relocation(coll_instru, reloc_text);
  printf("FOR .data\n");
  printf("RELOCATION COMPLETED.\n\n");

  // CREATION OF CODE BINAIRE
  printf("STARTING GENERATION OF CODE...\n");
  create_code_binaire(coll_instru, dicio_instru);
  print_Coll_INSTRU_with_code(coll_instru);

}
