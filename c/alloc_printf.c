#include "alloc_printf.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static char* alloc_vprintf(const char* format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    int size = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);
    if (size < 0) {
        return NULL;
    }
    char* buffer = malloc(size + 1);
    if (buffer == NULL) {
        return NULL;
    }
    vsnprintf(buffer, size + 1, format, args);
    return buffer;
}

char* alloc_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char* result = alloc_vprintf(format, args);
    va_end(args);
    return result;
}
