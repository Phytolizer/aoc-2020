#pragma once

#include <hedley.h>

char* alloc_printf(const char* format, ...) HEDLEY_PRINTF_FORMAT(1, 2);
