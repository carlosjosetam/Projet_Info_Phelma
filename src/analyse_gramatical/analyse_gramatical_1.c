#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "etiquette.c"
#include "verification_text.c"
#include "verification_data.c"
#include "verification_bss.c"
#include "division_section.c"

void analyse_gramatical_1(Lexeme_t * head_lexemes, Lexeme_t * head_text, Lexeme_t * head_data, Lexeme_t * head_bss, Etiquette_t * list_etiquettes, Dicio_Instru_t * dicio_instru) {

  division_section(head_lexemes, head_text, head_data, head_bss, dicio_instru);
  printf("LIST OF .TEXT\n");
  print_list(head_text);
  cherche_etiquette(head_text, list_etiquettes, "text");
  print_list(head_text);

  printf("LIST OF .DATA\n");
  print_list(head_data);
  cherche_etiquette(head_data, list_etiquettes, "data");
  print_list(head_data);

  printf("LIST OF .BSS\n");
  print_list(head_bss);
  cherche_etiquette(head_bss, list_etiquettes, "bss");
  print_list(head_bss);
}
