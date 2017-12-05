#include "../../include/notify.h"

#ifndef _Dicio_Instru
#define _Dicio_Instru

typedef struct Dicio_Instru {
  /* Linked list for Instructions dicionaire */
  /* operands: REG, IME, OFF, TAR, SA */
    char * word; /* ADD */
    int n_op; /* 3 */
    char * type; /* R */
    char * op1; /* REG */
    char * op2; /* REG */
    char * op3; /* REG */
    struct Binaire * bin;
    struct Dicio_Instru * next;
} Dicio_Instru_t;

typedef struct Binaire {
  /* Linked list for Instructions dicionaire for creating code binaire */
    char n_sections; /* number of sections */
    char code_binaire;

    char * sec1; /* SPECIAL */
    char * sec2; /* Rt */
    char * sec3;
    char * sec4;
    char * sec5;
    char * sec6;
    char * sec7;
    char * sec8;

} Binaire_t;

void print_Dicio_Instru(Dicio_Instru_t * head);

int n_op_Dicio_Instru(Dicio_Instru_t * head, char * word);
bool is_Instru_Dicio_Instru(Dicio_Instru_t * head, char * word);
char * get_section_bin(Dicio_Instru_t * head, char * word, int index);
int get_code_instru_bin(Dicio_Instru_t * head, char * word);
void push_Dicio_Instru(Dicio_Instru_t * head, char * word, int n_op, char * type, char * op1, char * op2, char * op3, Binaire_t * bin);
Dicio_Instru_t * new_Dicio_Instru();
Binaire_t * new_Binaire(char n_sections, char code_binaire, char * sec1, char * sec2, char * sec3, char * sec4, char * sec5, char * sec6, char * sec7, char * sec8);
char * get_addressing_type(Dicio_Instru_t * dicionaire, char * word, int index);

#endif
