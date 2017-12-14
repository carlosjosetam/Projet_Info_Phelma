#include "../../include/notify.h"

#ifndef _Coll_DATA
#define _Coll_DATA

typedef struct Coll_DATA{
  /* Linked list for COLL_DATA */
    char* directive; /* .SPACE */
    int n_op; /* 1 */
    int ligne; /* 11 */
    int decalage; /* 0 */
    char * valeur; /* ? */
    int type;
    int code_binaire;
    struct Coll_DATA * next;
} Coll_DATA_t;

void print_Coll_DATA(Coll_DATA_t * head);
void push_Coll_DATA(Coll_DATA_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur, int type);
Coll_DATA_t * new_Coll_DATA();
int get_address_by_line_data(Coll_DATA_t * head, int line);
int get_type_operand_directive(Coll_DATA_t * directive);
int get_address_directive(Coll_DATA_t * directive);
Coll_DATA_t * get_next_directive(Coll_DATA_t * directive);
char * get_operand_directive(Coll_DATA_t * directive);
int get_line_directive(Coll_DATA_t * directive);
void push_code_binaire_data(Coll_DATA_t * directive, int code_binaire);
int get_value_int_operand_directive(Coll_DATA_t * directive);
void print_Coll_DATA_with_code(Coll_DATA_t * head);
int get_max_lines_data(Coll_DATA_t * head);

#endif
