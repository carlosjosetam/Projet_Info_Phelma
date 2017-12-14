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
    int value_int_op1;
    int value_int_op2;
    int value_int_op3;
    int code_binaire_instru;

    struct Coll_INSTRU * next;
} Coll_INSTRU_t;

void print_Coll_INSTRU(Coll_INSTRU_t * head);
void print_Coll_INSTRU_with_code(Coll_INSTRU_t * head);
void push_Coll_INSTRU(Coll_INSTRU_t * head, char * instruction, int n_op, int ligne, int decalage, char * op1, char * op2, char * op3, int type_op1, int type_op2, int type_op3);
Coll_INSTRU_t * new_Coll_INSTRU();
void push_code_binaire_instru(Coll_INSTRU_t * instru, int code_binaire_instru);
int get_value_operand(Coll_INSTRU_t * instruction, int index);
int get_base_from_base_offset(Coll_INSTRU_t * instruction);
int get_offset_from_base_offset(Coll_INSTRU_t * instruction);
int get_number_operands(Coll_INSTRU_t * instruction);
Coll_INSTRU_t * next_instru(Coll_INSTRU_t * instruction);
char * get_operand(Coll_INSTRU_t * instruction, int index);
int get_type_operand(Coll_INSTRU_t * instruction, int index);
char * get_name_instruction(Coll_INSTRU_t * instruction);
int get_line(Coll_INSTRU_t * instruction);
int get_address_instru(Coll_INSTRU_t * instruction);
int get_address_by_line_text(Coll_INSTRU_t * head, int line);
void put_operand_value_int(Coll_INSTRU_t * instruction, int index, int value);
bool relocate_symbole(Coll_INSTRU_t * head, int address_instru, char * symbole, int new_address);
int get_max_lines_instru(Coll_INSTRU_t * head);
int get_code_binaire_final(Coll_INSTRU_t * head);

#endif
