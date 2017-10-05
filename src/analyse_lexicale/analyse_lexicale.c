#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "canonisation.h"
#include "aef.h"
#include "../structures/list_lexeme.h"

void analyse_lexicale(char * path, Lexeme_t * list) {
  FILE* file = fopen(path, "r"); /* should check the result */
  char ligne[256];
  // compteur de ligne
  int comp_ligne = 1;

  while (fgets(ligne, sizeof(ligne), file)) { // chaque ligne

    printf("Ligne lit pour MAIN ==> %s\n", ligne);
    char* n_ligne = strdup(canon(ligne));
  	printf("Main reponse ==> %s\n\n", strdup(n_ligne));
    printf("Analyse Lexicale:\n");
    aef(n_ligne, comp_ligne);

    comp_ligne++;
  }

  printf("FIN DU FICHIER\n");
  fclose(file);
}
