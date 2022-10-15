#include "day01.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dyarray.h"
#include "slurp.h"
#include "strtok_reentrant.h"

typedef DYARRAY_TYPE(long) values_t;

int day01(const char* input_file) {
    slurp_result_t input_result = slurp_file(input_file);
    if (input_result.error) {
        fprintf(stderr, "Error reading input file: %s\n", input_result.error);
        free(input_result.error);
        return 1;
    }

    int ret = 0;
    char* save;
    values_t values = DYARRAY_NEW;
    for (char* line = strtok_reentrant(input_result.value, "\n", &save); line != NULL;
         line = strtok_reentrant(NULL, "\n", &save)) {
        errno = 0;
        long value = strtol(line, NULL, 10);
        if (errno != 0) {
            fprintf(stderr, "Error parsing line '%s': %s\n", line, strerror(errno));
            ret = 1;
            break;
        }
        DYARRAY_PUSH(&values, value);
    }
    free(input_result.value);

    if (ret != 0) {
        DYARRAY_FREE(values);
        return ret;
    }

    // find 2 entries that sum to 2020
    for (size_t i = 0; i < values.size; i++) {
        for (size_t j = i + 1; j < values.size; j++) {
            if (values.data[i] + values.data[j] == 2020) {
                printf(
                    "Part 1: %ld * %ld = %ld\n", values.data[i], values.data[j],
                    values.data[i] * values.data[j]
                );
            }
        }
    }

    // find 3 entries that sum to 2020
    for (size_t i = 0; i < values.size; i++) {
        for (size_t j = i + 1; j < values.size; j++) {
            for (size_t k = j + 1; k < values.size; k++) {
                if (values.data[i] + values.data[j] + values.data[k] == 2020) {
                    printf(
                        "Part 2: %ld * %ld * %ld = %ld\n", values.data[i], values.data[j],
                        values.data[k], values.data[i] * values.data[j] * values.data[k]
                    );
                }
            }
        }
    }

    DYARRAY_FREE(values);
    return ret;
}
