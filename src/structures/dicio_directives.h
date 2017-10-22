#ifndef _Dicio_Directives
#define _Dicio_Directives

typedef struct type_directive {
  // structure for type and value VERIFICATION
  int type; // INT (DECIMAL)
  char * max_value; // -128
  char * min_value; // -18
} type_directive_t;

typedef struct Dicio_Directives {
  // Linked list for DIRECTIVES dicionaire
    char* word; // .SPACE
    int n_op; // 1
    int type_permit; // DECIMAL
    int type_permit_2;
    int type_permit_3;
    struct type_directive * type_test;
    struct Dicio_Directives * next;
} Dicio_Directives_t;

void print_Dicio_Directives(Dicio_Directives_t * head);
bool is_Dir_in_Dicio_Directives(Dicio_Directives_t * head, char * word);
void push_Dicio_Directives(Dicio_Directives_t * head, char* word, int n_op, int type_permit, int type_permit_2, int type_permit_3, type_directive_t * type_test);
int type_permit_directive(Dicio_Directives_t * head, char * word);
bool is_type_permit_directive(Dicio_Directives_t * head, char * word, int type);
bool is_value_permit_directive(Dicio_Directives_t * head, char * word, int type, char * value);
bool is_in_interval_DECIMAL(int cmp, int max, int min);
bool is_in_interval_HEXA(char * cmp, char * max_value, char * min_value);
Dicio_Directives_t * new_Dicio_Directives();
type_directive_t * new_Type_Directive(int type, char * max_value, char * min_value);


#endif
