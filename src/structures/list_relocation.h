#include "../../include/notify.h"
#ifndef _Relocation
#define _Relocation

typedef struct Relocation {
  /* Linked list with first HEAD element non */
  /* acessible. */
    int address_instru;
    int address_etiquette;
    char * section;
    char * type_relocation;
    char * symbole;

    struct Relocation * next;
} Relocation_t;

void print_list_relocation(Relocation_t * head);
void push_Relocation(Relocation_t * head, int address_instru, int address_etiquette, char * section, char * type_relocation, char * symbole);
bool is_empty_Relocation(Relocation_t * head);
Relocation_t * new_Relocation();

#endif
