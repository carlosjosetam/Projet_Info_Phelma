#include "../structures/list_etiquette.h"
#include "../structures/dicio_directives.h"
#include "../structures/dicio_instru.h"

void analyse_gramatical_1(Lexeme_t * head_lexemes, Lexeme_t * head_text, Lexeme_t * head_data, Lexeme_t * head_bss, Etiquette_t * list_etiquettes, Dicio_Instru_t * dicio_instru, Dicio_Directives_t * dicio_directives);
bool is_next_same_line(Lexeme_t * current, int current_line);
