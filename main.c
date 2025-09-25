#include "custom_printf.h"
#include <stdio.h>

static void newline(void) { putchar('\n'); } // New line function to shorten input 

int main(void) {

    // Character
    customPrintf("Character: %c", 'A');
    newline();

    // String
    customPrintf("String: %s", "Hello, World!");
    newline();

    // Integer
    customPrintf("Integer: %d", 42);
    newline();

    // Binary
    customPrintf("Binary: %b", 5);
    newline();

    // Percent Sign
    customPrintf("Percent sign: %");
    newline();

    // Nonspecifier
    customPrintf("Nonspecifier");
    newline();

    // Null
    customPrintf(NULL);
    newline();
}
