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
