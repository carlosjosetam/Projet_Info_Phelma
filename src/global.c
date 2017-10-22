//Program root
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int hex2int(char * hex) {

    int val = 0;
    uint8_t byte = *hex++; byte = *hex++; // JUMP TWO FIRSTS ELEMENTS
    while (*hex) {
        // get current character then increment
        byte = *hex++;
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        val = (val << 4) | (byte & 0xF);
    }
    return val;
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

bool is_in_interval_HEXA(char * cmp, char * max_value, char * min_value) { // Verfifies by size
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
