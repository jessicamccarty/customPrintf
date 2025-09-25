#ifndef CUSTOM_PRINTF_H
#define CUSTOM_PRINTF_H

#include <stdarg.h> // Library includes va_list, va_start, va_arg, va_end
#include <stddef.h> // Library includes size_t

int customPrintf(const char *formatString, ...);

#endif 