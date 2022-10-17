#include "day03.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dyarray.h"
#include "slurp.h"
#include "strtok_reentrant.h"

typedef DYARRAY_TYPE(const char*) StringArray;

typedef struct {
    size_t dx;
    size_t dy;
} Slope;

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

static size_t count_trees(StringArray input, Slope slope) {
    size_t x = 0;
    size_t y = 0;
    size_t trees = 0;
    size_t width = strlen(input.data[0]);
    while (y < input.size) {
        if (input.data[y][x] == '#') {
            trees++;
        }
        x = (x + slope.dx) % width;
        y += slope.dy;
    }
    return trees;
}

int day03(const char* input_file) {
    slurp_result_t input = slurp_file(input_file);
    if (input.error) {
        fprintf(stderr, "Error reading input file: %s\n", input.error);
        free(input.error);
        return 1;
    }

    char* save;
    StringArray lines = DYARRAY_NEW;
    for (char* line = strtok_reentrant(input.value, "\n", &save); line != NULL;
         line = strtok_reentrant(NULL, "\n", &save)) {
        DYARRAY_PUSH(&lines, line);
    }

    printf("Part 1: %zu\n", count_trees(lines, (Slope){3, 1}));

    Slope slopes[] = {
        {.dx = 1, .dy = 1}, {.dx = 3, .dy = 1}, {.dx = 5, .dy = 1},
        {.dx = 7, .dy = 1}, {.dx = 1, .dy = 2},
    };

    size_t total = 1;
    for (size_t i = 0; i < ARRAY_LEN(slopes); i++) {
        total *= count_trees(lines, slopes[i]);
    }

    printf("Part 2: %zu\n", total);

    DYARRAY_FREE(lines);
    free(input.value);
    return 0;
}
