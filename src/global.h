#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_in_interval_DECIMAL(char * cmp, char * max_value, char * min_value);
bool is_in_interval_HEXA(char * cmp, char * max_value, char * min_value);
int hex2int(char * hex);
char * to_uppercase(char * word);
char* strupr(char* s);
int octa2int(char * number);
void showbits(unsigned int x);
