#include <assert.h>
#include <errno.h>
#include <limits.h>
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
                } else {
                    *(int*)opt->value += 1;
                }
                if (*(int*)opt->value < 0) {
                    *(int*)opt->value = 0;
                }
                break;
            case ARGP_OPT_BIT:
                if (flags & OPT_UNSET) {
                    *(int*)opt->value &= ~opt->data;
                } else {
                    *(int*)opt->value |= opt->data;
                }
                break;
            case ARGP_OPT_STR:
                if (argp->opt_value != NULL) {
                    *(const char**)opt->value = argp->opt_value;
                    argp->opt_value = NULL;
                } else if (argp->argc > 1) {
                    argp->argc -= 1;
                    *(const char**)opt->value = *argp->argv;
                    argp->argv += 1;
                } else {
                    argp_error(argp, opt, "requires a value", flags);
                }
            case ARGP_OPT_INT:
                errno = 0;
                if (argp->opt_value != NULL) {
                    long value = strtol(argp->opt_value, (char**)&s, 0);
                    if (value < INT_MIN || value > INT_MAX) {
                        argp_error(argp, opt, "numerical result out of range", flags);
                    }
                    *(int*)opt->value = (int)value;
                    argp->opt_value = NULL;
                } else if (argp->argc > 1) {
                    argp->argc -= 1;
                    long value = strtol(*argp->argv, (char**)&s, 0);
                    argp->argv += 1;
                    if (value < INT_MIN || value > INT_MAX) {
                        argp_error(argp, opt, "numerical result out of range", flags);
                    }
                    *(int*)opt->value = (int)value;
                } else {
                    argp_error(argp, opt, "requires a value", flags);
                }
                if (errno == ERANGE) {
                    argp_error(argp, opt, "numerical result out of range", flags);
                }
                if (s != NULL && s[0] != '\0') {
                    argp_error(argp, opt, "expects an integer value", flags);
                }
                break;
            case ARGP_OPT_FLOAT:
                errno = 0;
                if (argp->opt_value != NULL) {
                    *(float*)opt->value = strtof(argp->opt_value, (char**)&s);
                    argp->opt_value = NULL;
                } else if (argp->argc > 1) {
                    argp->argc -= 1;
                    *(float*)opt->value = strtof(*argp->argv, (char**)&s);
                    argp->argv += 1;
                } else {
                    argp_error(argp, opt, "requires a value", flags);
                }
                if (errno == ERANGE) {
                    argp_error(argp, opt, "numerical result out of range", flags);
                }
                if (s != NULL && s[0] != '\0') {
                    argp_error(argp, opt, "expects a numerical value", flags);
                }
                break;
            default:
                assert(false && "unreachable");
        }
    }

    if (opt->callback != NULL) {
        return opt->callback(argp, opt);
    }
    return 0;
}

static void argp_options_check(const struct argp_option* options) {
    for (size_t i = 0; options[i].type != ARGP_OPT_END; i += 1) {
        switch (options[i].type) {
            case ARGP_OPT_END:
            case ARGP_OPT_BOOL:
            case ARGP_OPT_BIT:
            case ARGP_OPT_INT:
            case ARGP_OPT_FLOAT:
            case ARGP_OPT_STR:
            case ARGP_OPT_GROUP:
                break;
            default:
                fprintf(stderr, "wrong option type: %d\n", options[i].type);
                break;
        }
    }
}

static int argp_short_opt(struct argp* argp, const struct argp_option* options) {
    for (size_t i = 0; options[i].type != ARGP_OPT_END; i += 1) {
        if (options[i].short_name == *argp->opt_value) {
            if (argp->opt_value[1]) {
                argp->opt_value += 1;
            } else {
                argp->opt_value = NULL;
            }
        }
    }
    return -2;
}

static int argp_long_opt(struct argp* argp, const struct argp_option* options) {
    for (size_t i = 0; options[i].type != ARGP_OPT_END; i += 1) {
        if (!options->long_name) {
            continue;
        }
    }
}
