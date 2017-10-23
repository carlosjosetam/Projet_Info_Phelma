#include "../../include/notify.h"

#ifndef _Dicio_Instru
#define _Dicio_Instru

typedef struct Dicio_Instru{
  // Linked list for Instructions dicionaire
    char* word; // ADD
    int n_op; // 3
    int code_bin; //100001
    struct Dicio_Instru * next;
} Dicio_Instru_t;

void print_Dicio_Instru(Dicio_Instru_t * head);

int n_op_Dicio_Instru(Dicio_Instru_t * head, char * word);
bool is_Instru_Dicio_Instru(Dicio_Instru_t * head, char * word);

void push_Dicio_Instru(Dicio_Instru_t * head, char* word, int n_op, int code_bin);
Dicio_Instru_t * new_Dicio_Instru();

#endif
