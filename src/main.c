/* Program root */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "structures/list_lexeme.h"
#include "structures/list_etiquette.h"
#include "structures/dicio_instru.h"
#include "structures/dicio_directives.h"
#include "structures/coll_bss.h"
#include "global.h"
#include "notify.h"
#include "main.h"

#include "analyse_lexicale/analyse_lexicale.h"
#include "analyse_gramatical/analyse_gramatical_1.h"


int main (int argc, char ** argv ) {
  if (argc != 2) {
    ERROR_MSG("Number of arguments incorrect. Check path");
  }
  char * path = argv[1];


  printf("ASSEMBLEUR MIPS ==>> Projet Info PHELMA 2017\n");
  printf("Selected file: %s\n", path);
  /*CREATION DE DICIONIRE D'INSTRUCTIONS */
  Dicio_Instru_t * dicio_instru = new_Dicio_Instru();
  print_Dicio_Instru(dicio_instru);

  /*CREATION DE DICIONIRE DE DIRECTIVES */
  Dicio_Directives_t * dicio_directives = new_Dicio_Directives();
  print_Dicio_Directives(dicio_directives);

  /*CREATION DE LIST CHAINEE */
  Lexeme_t * list_complet = new_lexeme();
  Lexeme_t * list_text = new_lexeme();
  Lexeme_t * list_data = new_lexeme();
  Lexeme_t * list_bss = new_lexeme();

  Etiquette_t *etiq1 = new_etiquette();

  analyse_lexicale(path, list_complet);

  analyse_gramatical_1(list_complet, list_text, list_data, list_bss, etiq1, dicio_instru, dicio_directives);

  printf("%s\n", to_uppercase("hello :)"));
  printf("%d\n", octa2int("0123"));

  int op1 = 64;
  int binaire = (0b000000<<5) | op1;
  binaire = (binaire<<5) | op1;
  binaire = (binaire<<10)<<6 | 6;
  showbits(binaire);
  printf("%X\n", binaire);


  return 0;
}
