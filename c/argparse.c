#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argparse.h"

#define OPT_UNSET 1
#define OPT_LONG (1 << 1)

static const char* prefix_skip(const char* str, const char* prefix) {
    size_t len = strlen(prefix);
    if (strncmp(str, prefix, len) != 0) {
        return NULL;
    }
    return str + len;
}

static int prefix_cmp(const char* str, const char* prefix) {
    while (true) {
        if (*prefix == '\0') {
            return 0;
        }
        if (*str != *prefix) {
            return (uint8_t)*prefix - (uint8_t)*str;
        }
        str += 1;
        prefix += 1;
    }
}

static void argp_error(struct argp* argp, const struct argp_option* opt, const char* reason,
                       int flags) {
    (void)argp;
    if (flags & OPT_LONG) {
        fprintf(stderr, "error: option '--%s' %s\n", opt->long_name, reason);
    } else {
        fprintf(stderr, "error: option '-%c' %s\n", opt->short_name, reason);
    }
    exit(EXIT_FAILURE);
}

static int argp_get_value(struct argp* argp, const struct argp_option* opt, int flags) {
    const char* s = NULL;
    if (opt->value) {
        switch (opt->type) {
            case ARGP_OPT_BOOL:
                if (flags & OPT_UNSET) {
                    *(int*)opt->value -= 1;
                }
                break;
        }
    }
}
