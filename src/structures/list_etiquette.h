typedef struct Etiquette Etiquette_t;

void print_list_etiquette(Etiquette_t * head);
void push_etiquette(Etiquette_t * head, char* word, int ligne);
int pop_last_etiquette(Etiquette_t * head, char ** word);
int pop_first_etiquette(Etiquette_t * head, char ** word);
bool is_empty_etiquette(Etiquette_t * head);
Etiquette_t * new_etiquette();
bool is_in_list(Etiquette_t * head, char * word);
