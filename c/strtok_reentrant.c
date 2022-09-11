#include "strtok_reentrant.h"

#include <string.h>

char* strtok_reentrant(char* str, const char* delim, char** saveptr) {
    if (str == NULL) {
        str = *saveptr;
    }

    str += strspn(str, delim);
    if (*str == '\0') {
        return NULL;
    }

    char* end = str + strcspn(str, delim);
    if (*end == '\0') {
        *saveptr = end;
        return str;
    }

    *end = '\0';
    *saveptr = end + 1;

    return str;
}
