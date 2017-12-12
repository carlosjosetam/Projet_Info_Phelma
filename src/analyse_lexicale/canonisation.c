#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "canonisation.h"

bool isCS(char c) {
	char* CS = ":,#.-()$ ";
	int i;
	for (i = 0; i < strlen(CS); i++) {
		if(c == CS[i]) return true;
	}
	return false;
}

bool isCS2(char c) {
	char* CS = ":,-()";
	int i;
	for (i = 0; i < strlen(CS); i++) {
		if(c == CS[i]) return true;
	}
	return false;
}

char* canon(char *ligne) {
	/*printf("Code a canoniser: %s\n", ligne); */

	char n_ligne[256];
	int k;
	for (k = 0; k < strlen(n_ligne); k++) {
		n_ligne[k] = ' ';
	}

	int j = 0; /*compteur pour creer nouveau ligne */

	/*printf("Ligne vide: %s\n", n_ligne); */

	int i; /* compteur pour ligne */
	for (i = 0; i < strlen(ligne); i++) {
		/*START */
		/*printf("START: %d\n", i); */

		if (ligne[i] == '$') { /*DOLLAR */
			n_ligne[j] = ligne[i]; j++; i++;
			/* LOOP */
			while(!(ligne[i] == '\0' || isCS(ligne[i]))) {
				n_ligne[j] = ligne[i]; j++; i++;
			}
			n_ligne[j] = ' '; j++; i--;
		}

		else if (ligne[i] == '.') { /*POINT */
			n_ligne[j] = ligne[i]; j++; i++;
			while (!(ligne[i] == '\0' || isCS(ligne[i]))) {
				n_ligne[j] = ligne[i]; j++; i++;
			}
			n_ligne[j] = ' '; j++; i--;
		}

		else if (isCS2(ligne[i]) && !(ligne[i] == '\0')) { /*CASE OF : , - ( ) */
			n_ligne[j] = ligne[i]; j++;
			n_ligne[j] = ' '; j++;
		}

		else if (ligne[i] == '#') { /*COMENTAIRE */
			i++;
			while (!(ligne[i] == '\0')) {
				i++; /*EFACER TOUT APRES */
			}
			n_ligne[j] = '\0';
		}
		else if (! isCS(ligne[i])) { /* CHAR NORMAL */
			n_ligne[j] = ligne[i]; j++; i++;
			while (! (isCS(ligne[i])) || ligne[i] == '\0') {
				n_ligne[j] = ligne[i]; j++; i++;
			}
			n_ligne[j] = ' '; j++; i--;
		}
		else if (ligne[i] == ' ') { /* EVITER ESPACES MULTIPLES */
			/*RIEN A FAIRE */
		}
	}

	n_ligne[j] = '\0';

	/*printf("Ligne canonisé: %s\n", n_ligne); */

	char* resultat = strdup(n_ligne);
	/*printf("resultat %s\n", resultat); */
	/*bonjour */
	return resultat;
}
