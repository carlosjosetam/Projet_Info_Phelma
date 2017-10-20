#include "../structures/dicio_instru.h"
#include "../structures/coll_instru.h"

Coll_INSTRU_t * analyse_text(Lexeme_t * head_text, Dicio_Instru_t * dicio_instru);
bool is_next_same_line(Lexeme_t * current, int current_line);
