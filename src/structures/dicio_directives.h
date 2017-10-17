#ifndef _Dicio_Directives
#define _Dicio_Directives

typedef struct Dicio_Directives{
  // Linked list for DIRECTIVES dicionaire
    char* word; // .SPACE
    int n_op; // 1
    int type_permit; // DECIMAL
    struct Dicio_Directives * next;
} Dicio_Directives_t;

void print_Dicio_Directives(Dicio_Directives_t * head);
int is_Instru_in_Dicio_Directives(Dicio_Directives_t * head, char * word);
bool is_n_op_correct_Dicio_Directives(Dicio_Directives_t * head, char * word, int n_op);
void push_Dicio_Directives(Dicio_Directives_t * head, char* word, int n_op, int type_permit);
Dicio_Directives_t * new_Dicio_Directives();

#endif
