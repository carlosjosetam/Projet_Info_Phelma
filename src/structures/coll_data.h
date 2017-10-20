#ifndef _Coll_DATA
#define _Coll_DATA

typedef struct Coll_DATA{
  // Linked list for COLL_DATA dicionaire
    char* directive; // .SPACE
    int n_op; // 1
    int ligne; // 11
    int decalage; // 0
    char * valeur; // ?
    struct Coll_DATA * next;
} Coll_DATA_t;

void print_Coll_DATA(Coll_DATA_t * head);
void push_Coll_DATA(Coll_DATA_t * head, char* directive, int n_op, int ligne, int decalage, char * valeur);
Coll_DATA_t * new_Coll_DATA();

#endif
