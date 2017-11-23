#include "../../include/notify.h"
#ifndef _Etiquette
#define _Etiquette

typedef struct Etiquette {
  // Linked list with first HEAD element non
  // acessible.
    char* word;
    int ligne;
    int decalage;
    char * section;
    struct Etiquette * next;
} Etiquette_t;

void print_list_etiquette(Etiquette_t * head);
void push_etiquette(Etiquette_t * head, char* word, int ligne, int decalage, char * section);
int pop_last_etiquette(Etiquette_t * head, char ** word);
int pop_first_etiquette(Etiquette_t * head, char ** word);
bool is_empty_etiquette(Etiquette_t * head);
Etiquette_t * new_etiquette();
bool is_in_list(Etiquette_t * head, char * word);
Etiquette_t * is_in_list_current(Etiquette_t * head, char * word);
int get_address_etiquette(Etiquette_t * head);
char * get_section_etiquette(Etiquette_t * head);

#endif
