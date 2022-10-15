#ifndef DYARRAY_H_
#define DYARRAY_H_

#include <stddef.h>
#include <stdlib.h>

#define DYARRAY_TYPE(type) \
    struct {               \
        type* data;        \
        size_t size;       \
        size_t capacity;   \
    }

#define DYARRAY_NEW \
    { NULL, 0, 0 }

#define DYARRAY_PUSH(array, value)                                                              \
    do {                                                                                        \
        if ((array)->size + 1 > (array)->capacity) {                                            \
            (array)->capacity = (array)->capacity * 2 + 1;                                      \
            (array)->data = realloc((array)->data, (array)->capacity * sizeof(*(array)->data)); \
            if ((array)->data == NULL) {                                                        \
                perror("DYARRAY_PUSH");                                                         \
                exit(EXIT_FAILURE);                                                             \
            }                                                                                   \
        }                                                                                       \
        (array)->data[(array)->size] = (value);                                                 \
        (array)->size++;                                                                        \
    } while (0)

#define DYARRAY_POP(array) ((array)->data[--(array)->size])

#define DYARRAY_FREE(array)   \
    do {                      \
        free((array).data);   \
        (array).data = NULL;  \
        (array).size = 0;     \
        (array).capacity = 0; \
    } while (0)

#endif  // DYARRAY_H_
