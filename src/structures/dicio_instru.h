typedef struct Dicio_Instru Dicio_Instru_t;

void print_Dicio_Instru(Dicio_Instru_t * head);
bool is_Instru_in_Dicio_Instru(Dicio_Instru_t * head, char * word);
bool is_n_op_correct_Dicio_Instru(Dicio_Instru_t * head, char * word, int n_op);
void push_Dicio_Instru(Dicio_Instru_t * head, char* word, int n_op, int code_bin);
Dicio_Instru_t * new_Dicio_Instru();
