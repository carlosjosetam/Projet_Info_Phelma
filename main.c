//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "canonisation.h"
#include "aef.h"

int main () {
  FILE* file = fopen("ass.s", "r"); /* should check the result */
  char ligne[256];

  while (fgets(ligne, sizeof(ligne), file)) { // chaque ligne

        printf("Ligne lit pour MAIN ==> %s\n", ligne);
        char* n_ligne = strdup(canon(ligne));
      	printf("Main reponse ==> %s\n\n", strdup(n_ligne));
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */
       printf("FIN DU FICHIER\n");
  fclose(file);


	return 0;
}
