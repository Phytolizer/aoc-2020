#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

// for strtoll()
#define _ISOC99_SOURCE
#include <stdlib.h>
#include <string.h>

#include "simple_flags.h"

typedef enum {
    FLAG_I64,
    FLAG_STR,
} flag_type_t;

typedef struct {
    flag_type_t type;
    const char* name;
    const char* description;
    union {
        int64_t* pi64;
        const char** pstr;
    } location;
    union {
        int64_t i64;
        const char* str;
    } default_value;
} flag_t;

typedef struct flags {
    flag_t* data;
    size_t length;
    size_t capacity;
} flags_t;

static void push_flag(flags_t* flags, flag_t flag) {
    if (flags->length + 1 > flags->capacity) {
        flags->capacity = flags->capacity * 2 + 1;
        flag_t* new_data = calloc(flags->capacity, sizeof(flag_t));
        if (new_data == NULL) {
            perror("push_flag");
            exit(EXIT_FAILURE);
        }
        memcpy(new_data, flags->data, flags->length * sizeof(flag_t));
        free(flags->data);
        flags->data = new_data;
    }

    flags->data[flags->length] = flag;
    flags->length += 1;
}

struct flags* flag_init(void) {
    return calloc(1, sizeof(flags_t));
}

void flag_int64(struct flags* flags, int64_t* location, const char* name, const char* description) {
    push_flag(flags, (flag_t){
                         FLAG_I64,
                         name,
                         description,
                         {.pi64 = location},
                         {.i64 = *location},
                     });
}

void flag_str(struct flags* flags, const char** location, const char* name,
              const char* description) {
    push_flag(flags, (flag_t){
                         FLAG_STR,
                         name,
                         description,
                         {.pstr = location},
                         {.str = *location},
                     });
}

typedef struct {
    int argc;
    char** argv;
    int pos;
} args_t;

static args_t args_init(int argc, char** argv) { return (args_t){argc, argv, 0}; }

static const char* args_next(args_t* args) {
    if (args->pos >= args->argc) {
        return NULL;
    }
    args->pos += 1;
    return args->argv[args->pos - 1];
}

static const char* args_peek(const args_t* args) {
    if (args->pos >= args->argc) {
        return NULL;
    }
    return args->argv[args->pos];
}

int flag_parse(struct flags* flags, int argc, char** argv) {
    args_t args = args_init(argc, argv);
    const char* program_name = args_next(&args);
    assert(program_name != NULL);

    while (true) {
        const char* arg = args_next(&args);
        if (arg == NULL || arg[0] != '-' || strcmp(arg, "--") == 0) {
            return args.pos;
        }

        flag_t* flag = NULL;
        for (size_t i = 0; i < flags->length; i += 1) {
            if (strcmp(arg + 1, flags->data[i].name) == 0) {
                flag = &flags->data[i];
                break;
            }
        }

        if (flag == NULL) {
            flag_print_help(flags, program_name, stderr);
            fprintf(stderr, "ERROR: unknown flag %s\n", arg);
            exit(EXIT_FAILURE);
        }

        const char* value = args_peek(&args);
        if (value == NULL || value[0] == '-') {
            continue;
        }
        args_next(&args);
        switch (flag->type) {
            case FLAG_I64: {
                char* endp;
                errno = 0;
                long long parsed_value = strtoll(value, &endp, 10);
                if (errno == ERANGE || parsed_value < INT64_MIN || parsed_value > INT64_MAX ||
                    *endp != '\0') {
                    flag_print_help(flags, program_name, stderr);
                    fprintf(stderr, "ERROR: invalid value for int64: %s\n", value);
                    exit(EXIT_FAILURE);
                }
                *flag->location.pi64 = (int64_t)parsed_value;
                break;
            }
            case FLAG_STR:
                *flag->location.pstr = value;
                break;
        }
    }
}

void flag_print_help(const struct flags* flags, const char* program_name, FILE* stream) {
    fprintf(stream, "usage: %s [OPTIONS]\n", program_name);
    fprintf(stream, "  OPTIONS:\n");
    for (size_t i = 0; i < flags->length; i += 1) {
        flag_t* flag = &flags->data[i];
        fprintf(stream, "    -%s\n", flag->name);
        fprintf(stream, "        %s\n", flag->description);
        fprintf(stream, "        (default: ");
        switch (flag->type) {
            case FLAG_I64:
                fprintf(stream, "%" PRIu64, flag->default_value.i64);
                break;
            case FLAG_STR:
                fprintf(stream, "%s", flag->default_value.str);
                break;
        }
        fprintf(stream, ")\n");
    }
}

void flag_free(struct flags* flags) {
    free(flags->data);
    free(flags);
}
