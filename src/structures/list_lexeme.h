typedef struct Lexeme Lexeme_t;

void print_list(Lexeme_t * head);
void push(Lexeme_t * head, char* word, int type, int ligne);
int pop_last(Lexeme_t * head, char ** word);
int pop_first(Lexeme_t * head, char ** word);
bool is_empty(Lexeme_t * head);
Lexeme_t * next_lexeme(Lexeme_t * head);
Lexeme_t * new_lexeme();
int type_lexeme(Lexeme_t * head);
char * word_lexeme(Lexeme_t * head);
int ligne_lexeme(Lexeme_t * head);
