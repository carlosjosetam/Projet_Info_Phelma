#include "../structures/coll_bss.h"
#include "../structures/coll_instru.h"
#include "../structures/coll_data.h"

void cherche_etiquette(Lexeme_t * list_lexemes, Etiquette_t * list_etiquettes, char * section);
void update_address_etiquettes(Etiquette_t * list_etiquettes, Coll_BSS_t * coll_bss, Coll_INSTRU_t * coll_instru, Coll_DATA_t * coll_data);
