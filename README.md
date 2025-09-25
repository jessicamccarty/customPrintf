# customPrintf

A small, learning-focused implementation of `printf` in C that supports `%c`, `%s`, `%d`, `%i`, `%b` (binary), `%%`, and prints non-specifier characters as-is. It uses `putchar` and avoids the standard `printf`.


## Project Description

**Goal:** Recreate a tiny version of `printf` so we understand how format strings, `va_list`, and character output work under the hood.

**Supported specifiers**
- `%c` print a single character
- `%s` print a C string
- `%d` and `%i` print a signed decimal integer
- `%b` print an unsigned integer in binary
- `%%` print the percent character

## Group Members

- Jessica McCarty
- Avery Stafford

## How It Works

1. We loop through each character in format. If it is not %, we write it with `putchar`. If it is `%`, we look at the next character to decide the specifier.
2. We read values with `va_arg`. `%d` consumes an `int`, `%s` consumes a `char *`, `%c` consumes an `int` that we cast to `char`.
3. For `%d` and `%i`, we convert a signed int to decimal. We handle the sign by promoting to a wider type (`long long`) to avoid overflow with `INT_MIN`. We build digits into a temporary buffer in reverse, then flip them before printing. For `%b`, we convert an unsigned integer to binary. We take the least significant bit repeatedly and push characters into a temp array, then reverse to get the proper order.
4. Each helper function returns how many characters it printed. We add these to a running total and return it at the end, similar to printf.
5. Edge cases are handled accordingly: format == NULL prints Error: formatString is NULL, `%` followed by an unknown letter is ignored per assignment guidelines, NULL strings for `%s` print (null) to avoid a crash.

## How to Build and Run

### Prerequisites
- C compiler that supports C11
- We developed with `gcc` and `-std=c11`

### Build Commands

Generic:
```bash
gcc -Wall -Wextra -Werror -pedantic -std=c11 -o main main.c custom_printf.c
