#include "../../include/notify.h"

#ifndef _Coll_BSS
#define _Coll_BSS

typedef struct Coll_BSS{
  // Linked list for COLL_BSS
    char* directive; // .SPACE
    int n_op; // 1
    int ligne; // 11
    int decalage; // 0
    char * valeur; // DECIMAL
    struct Coll_BSS * next;
} Coll_BSS_t;

void print_Coll_BSS(Coll_BSS_t * head);
void push_Coll_BSS(Coll_BSS_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur);
Coll_BSS_t * new_Coll_BSS();
int get_address_by_line_bss(Coll_BSS_t * head, int line);
#endif
