//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "canonisation.h"

int main () {
	char* ligne = strdup("ADD $2,$3,$8ADD $2,$3,$8ADD $2,$3,$8ADD $2,$3,$8");
	char* nova = strdup(canon(ligne));

	printf("\nMain reponse: %s\n", nova);

	return 0;
}
