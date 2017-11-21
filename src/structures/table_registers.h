#include "../../include/notify.h"

#ifndef _Registers
#define _Registers

typedef struct Registers{
  // Linked list for Registers_t
    char * word;
    unsigned char number;
    struct Registers * next;
} Registers_t;


#endif


void print_Registers(Registers_t * head);
void push_Registers(Registers_t * head, char * word, unsigned char number);
Registers_t * new_Registers();
