/* Program global */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "global.h"
#include <math.h>


bool strcmp_not_case_sensitive(char * cmp1, char * cmp2) {
  if (strlen(cmp1) != strlen(cmp2)) return false;

  /* else */
  int i = 0;
  for (i = 0; i<strlen(cmp1); i++) {
    if (toupper(cmp1[i]) != toupper(cmp2[i])) return false;
  }
  return true;
}

char* strupr(char* s)
{
    char* tmp = s;

    for (;*tmp;++tmp) {
        *tmp = toupper((unsigned char) *tmp);
    }

    return s;
}

int octa2int(char * number)
{
    int octalNumber = atoi(number);
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0)
    {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}

void showbits(unsigned int x)
{
    int i;
    for(i=(sizeof(int)*8)-1; i>=0; i--) {
      (x&(1u<<i))?putchar('1'):putchar('0');
    }
    printf("\n");
    printf("0x%X\n", x);
}

void write_bits(unsigned int x, FILE * file)
{
    int i;
    for(i=(sizeof(int)*8)-1; i>=0; i--) {
      (x&(1u<<i))?fprintf(file, "1"):fprintf(file, "0");
    }
}


int hex2int(char * hex) {

    bool minus;
    int val = 0;
    int byte = *hex; /* JUMP TWO FIRSTS ELEMENTS */
    if (byte == '-') {
      byte = *hex++; byte = *hex++; byte = *hex++;
      minus = true;
    }
    else {
      byte = *hex++; byte = *hex++;
      minus = false;
    }

    while (*hex) {
        /* get current character then increment */
        byte = *hex++;

        /* transform hex character to the 4bit equivalent number, using the ascii table indexes */
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        /* shift 4 to make space for new digit, and add the 4 bits of the new digit */
        val = (val << 4) | (byte & 0xF);
    }

    if (minus) return 65536-val;
    else return val;
}

bool is_in_interval_DECIMAL(char * cmp, char * max_value, char * min_value) {
  int cmp_int = atoi(cmp);
  int max_value_int = atoi(max_value);
  int min_value_int = atoi(min_value);

  if (cmp_int <= max_value_int) {
    if (cmp_int >= min_value_int) {
      return true;
    }
  }
  return false;
}

bool is_in_interval_HEXA(char * cmp, char * max_value, char * min_value) { /* Verfifies by size */
  int cmp_hex = hex2int(cmp);
  int max_value_hex = hex2int(max_value);
  int min_value_hex = hex2int(min_value);

  if (cmp_hex <= max_value_hex) {
    if (cmp_hex >= min_value_hex) {
      return true;
    }
  }
  return false;
}
