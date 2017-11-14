#include "../../include/notify.h"

#ifndef _Coll_INSTRU
#define _Coll_INSTRU

typedef struct Coll_INSTRU {
  // Linked list for Coll_INSTRU
    char * instruction; // ADD
    int n_op; // 1
    int ligne; // 11
    int decalage; // 0
    char * op1; // ?
    char * op2;
    char * op3;
    int type_op1;
    int type_op2;
    int type_op3;

    struct Coll_INSTRU * next;
} Coll_INSTRU_t;

void print_Coll_INSTRU(Coll_INSTRU_t * head);
void push_Coll_INSTRU(Coll_INSTRU_t * head, char * instruction, int n_op, int ligne, int decalage, char * op1, char * op2, char * op3, int type_op1, int type_op2, int type_op3);
Coll_INSTRU_t * new_Coll_INSTRU();

#endif
