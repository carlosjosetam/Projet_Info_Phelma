#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isCS(char c) {
	char *CS = ":,#.-()$ ";
	int i;
	for (i = 0; i < strlen(CS); i++) {
		if(c == CS[i]) return true;
	}
	return false;
}

char* canon(char *ligne) {
	
	char new_ligne[256];

	int i;
	for (i = 0; i < strlen(ligne); i++) {
		printf("%d\n", i);
		if(ligne[i] == '$') {
			strcat(new_ligne, "$"); i++;
			while(!(ligne[i] == '\0' || isCS(ligne[i]))) {
				strcat(new_ligne, "e"); i++;
			}
			strcat(new_ligne, " "); i = i-1;
		}
		else if(ligne[i] == '.') {
			strcat(new_ligne, "."); i++;
			while(!(ligne[i] == '\0' || isCS(ligne[i]))) {
				printf("dentro %d\n", i);
				strcat(new_ligne, &ligne[i]); i++;
			}
			printf("out");
			strcat(new_ligne, " "); i = i-1;
		}
		else if(ligne[i] == ',') {
			strcat(new_ligne, &ligne[i]); i++;
			strcat(new_ligne, " ");
		}	
	}		

	char *resultat = new_ligne;
	return resultat;
}


	

int main () {
	char *ligne = strdup("$7$2$4");
	char *new_ligne = canon(ligne);

	printf("\n%s\n", new_ligne);

	return 0;
}


	
