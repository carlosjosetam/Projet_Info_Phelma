#include "../../include/notify.h"

#ifndef _Coll_INSTRU
#define _Coll_INSTRU

typedef struct Coll_INSTRU {
  /* Linked list for Coll_INSTRU */
    char * instruction; /* ADD */
    int n_op; /* 1 */
    int ligne; /* 11 */
    int decalage; /* 0 */
    char * op1; /* ? */
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

int get_number_operands(Coll_INSTRU_t * instruction);
Coll_INSTRU_t * next_instru(Coll_INSTRU_t * instruction);
char * get_operand(Coll_INSTRU_t * instruction, int index);
int get_type_operand(Coll_INSTRU_t * instruction, int index);
char * get_name_instruction(Coll_INSTRU_t * instruction);
int get_line(Coll_INSTRU_t * instruction);
int get_address_instru(Coll_INSTRU_t * instruction);
int get_address_by_line_text(Coll_INSTRU_t * head, int line);

#endif
