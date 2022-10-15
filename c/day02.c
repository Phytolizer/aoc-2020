#include "day02.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dyarray.h"
#include "slurp.h"
#include "strdup_std.h"
#include "strtok_reentrant.h"

typedef struct {
    unsigned long begin;
    unsigned long end;
} RowRange;

typedef struct {
    char c;
    RowRange range;
    char* password;
} Row;

typedef DYARRAY_TYPE(const char*) StringArray;

typedef struct {
    char* allocated;
    StringArray array;
} SplitString;

static void splitstring_free(SplitString split) {
    free(split.allocated);
    DYARRAY_FREE(split.array);
}

static SplitString str_split(const char* str, const char* delim) {
    char* allocated = strdup_std(str);
    StringArray result = DYARRAY_NEW;
    char* save;
    for (char* token = strtok_reentrant(allocated, delim, &save); token != NULL;
         token = strtok_reentrant(NULL, delim, &save)) {
        DYARRAY_PUSH(&result, token);
    }
    return (SplitString){
        .allocated = allocated,
        .array = result,
    };
}

static Row row_from_string(const char* string) {
    SplitString colon_split = str_split(string, ":");
    const char* policy = colon_split.array.data[0];
    const char* password = colon_split.array.data[1];
    SplitString space_split = str_split(policy, " ");
    const char* range = space_split.array.data[0];
    const char* c = space_split.array.data[1];
    SplitString hyphen_split = str_split(range, "-");
    const char* begin = hyphen_split.array.data[0];
    const char* end = hyphen_split.array.data[1];
    Row result = {
        .c = *c,
        .range =
            {
                .begin = strtoul(begin, NULL, 10),
                .end = strtoul(end, NULL, 10),
            },
        .password = strdup_std(password + 1),
    };
    splitstring_free(colon_split);
    splitstring_free(space_split);
    splitstring_free(hyphen_split);
    return result;
}

static bool is_valid_part1(Row row) {
    size_t count = 0;
    for (const char* c = row.password; *c != '\0'; c++) {
        if (*c == row.c) {
            count++;
        }
    }
    return count >= row.range.begin && count <= row.range.end;
}

static bool is_valid_part2(Row row) {
    return (row.password[row.range.begin - 1] == row.c) ^
           (row.password[row.range.end - 1] == row.c);
}

int day02(const char* input_file) {
    slurp_result_t input_result = slurp_file(input_file);
    if (input_result.error) {
        fprintf(stderr, "Error reading input file: %s\n", input_result.error);
        free(input_result.error);
        return 1;
    }

    char* save;
    size_t valid_part1 = 0;
    size_t valid_part2 = 0;
    for (char* line = strtok_reentrant(input_result.value, "\n", &save); line != NULL;
         line = strtok_reentrant(NULL, "\n", &save)) {
        Row row = row_from_string(line);
        if (is_valid_part1(row)) {
            valid_part1++;
        }
        if (is_valid_part2(row)) {
            valid_part2++;
        }
        free(row.password);
    }

    printf("Part 1: %zu\n", valid_part1);
    printf("Part 2: %zu\n", valid_part2);

    free(input_result.value);
    return 0;
}
