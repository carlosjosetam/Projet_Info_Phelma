#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../structures/list_lexeme.h"
#include "../structures/list_etiquette.h"
#include "etiquette.h"
#include "division_section.h"
#include "analyse_bss.h"
#include "analyse_data.h"
#include "analyse_text.h"
#include "analyse_gramatical_1.h"
#include "analyse_symboles.h"


void analyse_gramatical_1(Lexeme_t * head_lexemes, Lexeme_t * head_text, Lexeme_t * head_data, Lexeme_t * head_bss, Etiquette_t * list_etiquettes, Dicio_Instru_t * dicio_instru, Dicio_Directives_t * dicio_directives) {

  print_list(head_lexemes);

  Lexeme_t * new_lexemes = analyse_symboles(head_lexemes);
  print_list(new_lexemes);

  division_section(new_lexemes, head_text, head_data, head_bss, dicio_instru);
  print_list(head_text);
  print_list(head_data);
  print_list(head_bss);

  printf("\nANALYSE D'ETIQUETTES EN COURS...\n");
  cherche_etiquette(head_text, list_etiquettes, "text");
  cherche_etiquette(head_data, list_etiquettes, "data");
  cherche_etiquette(head_bss, list_etiquettes, "bss");

  printf("LIST OF .TEXT\n");
  print_list(head_text);
  Coll_INSTRU_t * coll_instru = analyse_text(head_text, dicio_instru);
  print_Coll_INSTRU(coll_instru);


  printf("LIST OF .DATA\n");
  print_list(head_data);
  Coll_DATA_t * coll_data = analyse_data(head_data, dicio_directives);
  print_Coll_DATA(coll_data);

  printf("LIST OF .BSS\n");
  print_list(head_bss);
  Coll_BSS_t * coll_bss = analyse_bss(head_bss, dicio_directives);
  print_Coll_BSS(coll_bss);


  // ANALYSE TYPE INSTRUCTIONS
  analyse_type_instruction(coll_instru, dicio_instru);

}
