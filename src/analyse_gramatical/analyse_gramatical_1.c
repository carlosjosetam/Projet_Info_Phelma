#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "etiquette.c"
#include "verification_text.c"
#include "verification_data.c"
#include "verification_bss.c"

void analyse_gramatical_1(Lexeme_t * head_lexemes, Etiquette_t * list_etiquettes, Dicio_Instru_t * dicio_instru) {
  cherche_etiquette(head_lexemes, list_etiquettes);
  verification_text(head_lexemes, dicio_instru);
  verification_data(head_lexemes, dicio_instru);
  verification_bss(head_lexemes, dicio_instru);
}
