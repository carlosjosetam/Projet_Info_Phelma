//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "src/structures/list_lexeme.c"
#include "src/analyse_lexicale/analyse_lexicale.c"
#include "src/structures/dicio_instru.c"
#include "src/analyse_gramatical/analyse_gramatical_1.c"

int main (int argc, char ** argv ) {
  if (argc != 2) {
    printf("Number of arguments incorrect. Check path. ==> ABORT\n");
    abort();
  }
  char * path = argv[1];

  printf("ASSEMBLEUR MIPS ==>> Projet Info PHELMA 2017\n");
  printf("Selected file: %s\n", path);
  //CREATION DE DICIONIRE D'INSTRUCTIONS
  Dicio_Instru_t * dicio_instru = new_Dicio_Instru();
  print_Dicio_Instru(dicio_instru);

  //CREATION DE LIST CHAINEE
  Lexeme_t * list_complet = new_lexeme();
  Lexeme_t * list_text = new_lexeme();
  Lexeme_t * list_data = new_lexeme();
  Lexeme_t * list_bss = new_lexeme();

  Etiquette_t *etiq1 = new_etiquette();


  //if (is_empty(list1)) printf("EMPTY list\n");

  //printf("Liste du fichier ==>> ass.s\n");
  analyse_lexicale(path, list_complet);
  //print_list(list_complet);
  analyse_gramatical_1(list_complet, list_text, list_data, list_bss, etiq1, dicio_instru);

  // printf("Liste du fichier ==>> miam.s\n");
  // analyse_lexicale("tests/miam.s", list2);
  // print_list(list2);
  // cherche_etiquette(list2, etiq2);
  // print_list_etiquette(etiq2);
  //
  // printf("Liste du fichier ==>> mult.s\n");
  // analyse_lexicale("tests/mult.s", list3);
  // print_list(list3);
  // cherche_etiquette(list3, etiq3);
  // print_list_etiquette(etiq3);

  return 0;
}
