#include "strdup_std.h"

#include <stdlib.h>

char* strdup_std(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, str, len);
    return copy;
}
