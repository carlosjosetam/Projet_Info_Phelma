#include "../../include/notify.h"

#ifndef _Dicio_Instru
#define _Dicio_Instru

typedef struct Dicio_Instru {
  /* Linked list for Instructions dicionaire */
  /* operands: REG, IME, OFF, TAR, SA */

    char * word; /* ADD */
    int n_op; /* 3 */
    int code_bin; /*100001 */
    char * type; /* R */
    char * op1; /* REG */
    char * op2; /* REG */
    char * op3; /* REG */
    struct Dicio_Instru * next;
} Dicio_Instru_t;

void print_Dicio_Instru(Dicio_Instru_t * head);

int n_op_Dicio_Instru(Dicio_Instru_t * head, char * word);
bool is_Instru_Dicio_Instru(Dicio_Instru_t * head, char * word);

void push_Dicio_Instru(Dicio_Instru_t * head, char * word, int n_op, char * type, char * op1, char * op2, char * op3, int code_bin);
Dicio_Instru_t * new_Dicio_Instru();

char * get_addressing_type(Dicio_Instru_t * dicionaire, char * word, int index);

#endif
