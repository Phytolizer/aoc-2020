#ifndef ALLOC_PRINTF_H_
#define ALLOC_PRINTF_H_

#include <hedley.h>

char* alloc_printf(const char* format, ...) HEDLEY_PRINTF_FORMAT(1, 2);

#endif  // ALLOC_PRINTF_H_
