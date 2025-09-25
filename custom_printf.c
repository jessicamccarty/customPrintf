#include "custom_printf.h"
#include <stdio.h> // For putchar
#include <stdlib.h> // For malloc and free
#include <stdbool.h> // For bool
#include <limits.h> // for INT_MIN


// Helper Functions
// See notes for what they do 

// Writes one character and updates count. Returns 1 because it printed 1 character. 
static int write_char_counted(int ch) {
    putchar(ch);

    return 1;
}

// Writes a list of characters ending with a null character. Uses write_char_counted for each letter. If NULL, prints the word (null). Returns how many characters were printed.
static int write_cstring(const char *s) {
    int wrote = 0;

    if (s == NULL) {
        const char *fallback = "(null)";
        while (*fallback) { wrote += write_char_counted(*fallback++); }

        return wrote;
    }

    while (*s) { wrote += write_char_counted(*s++); }

    return wrote;
}


// Turns a signed integer into a heap string. If number is 0, returns "0". If negative, it flips to positive for counting digits.
// Pulls off digits from the end using % 10, stores them backward in temporary array, then adds minus sign back if needed.
// Allocates new string on the heap with malloc, copies digits in order, then returns new string. 
static char *itoa_decimal(int value) {
    char temp[16];
    int idx = 0;

    // This portion handles zero
    if (value == 0) {
        char *buf = (char *)malloc(2);
        if (!buf) return NULL;
        buf[0] = '0';
        buf[1] = '\0';

        return buf;
    }

    // Track the sign and make working copy as long long to avoid UB on INT_MIN
    bool negative = value < 0;
    long long v = value;
    if (negative) v = -(long long)value;

    // Build digits in reverse
    while (v > 0 && idx < (int)sizeof(temp) - 1) {
        int digit = (int)(v % 10);
        temp[idx++] = (char)('0' + digit);
        v /= 10;
    }

    // Account for the sign
    if (negative) temp[idx++] = '-';

    // Null terminate temp as reverse buffer
    temp[idx] = '\0';

    // Reverse into heap buffer
    int len = idx;

    char *out = (char *)malloc((size_t)len + 1);
    if (!out) return NULL;

    for (int i = 0; i < len; ++i) {
        out[i] = temp[len - 1 - i];
    }

    out[len] = '\0';

    return out;

}



// Turns unsigned number into a strings of 0s and 1s. If number is 0, returns "0". If not 0, looks at the end with value & 1, saves that, and then shifts number to right with value >>=1.
// The digits will come out backwards so it reverses them correctly and returns it. 
static char *utoa_binary(unsigned int value) {
    char temp[33];
    int idx = 0;

    if (value == 0) {
        char *buf = (char *)malloc(2);
        if (!buf) return NULL;
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }

    while (value > 0 && idx < 32) {
        temp[idx++] = (char)('0' + (value & 1u));
        value >>= 1;
    }

    temp[idx] = '\0';

    int len = idx;
    char *out = (char *)malloc((size_t)len + 1);
    if (!out) return NULL;

    for (int i = 0; i < len; ++i) {
        out[i] = temp[len - 1 - i];
    }

    out[len] = '\0';

    return out;
}


// Need main format code with switch statement
int customPrintf(const char *formatString, ...) {
    int total_written = 0;

    // NULL handler
    if (formatString == NULL) {
        total_written += write_cstring("Error: formatString is NULL");

        return total_written;
    }

    va_list args;
    va_start(args, formatString);


    for(const char *x = formatString; *x != '\0'; ++x) {
        if (*x != '%') {
            total_written += write_char_counted(*x);

            continue;
        }

        ++x;
        if (*x == '\0') {
            total_written += write_char_counted('%');

            break;
        }

        switch (*x) {
            case 'c': {
                // print a single character argument
                int ch = va_arg(args, int);
                total_written += write_char_counted(ch);
                break;
            }
            case 's': {
                // print a C string argument, falling back to (null)
                const char *str = va_arg(args, const char *);
                total_written += write_cstring(str);
                break;
            }
            case 'd':
            case 'i': {
                // print a signed decimal integer
                int value = va_arg(args, int);
                char *digits = itoa_decimal(value);
                if (!digits) {
                    va_end(args);
                    return -1;
                }
                total_written += write_cstring(digits);
                free(digits);
                break;
            }
            case 'b': {
                // print an unsigned integer in binary form
                unsigned int value = va_arg(args, unsigned int);
                char *bits = utoa_binary(value);
                if (!bits) {
                    va_end(args);
                    return -1;
                }
                total_written += write_cstring(bits);
                free(bits);
                break;
            }
            case '%': {
                // print a literal percent sign increments count by one %% -> %
                total_written += write_char_counted('%'); // 
                break;
            }
            default: {
                // ignore unsupported specifiers per assignment requirements
                break;
            }

        }

    }

    va_end(args);
    
    return total_written;
}
