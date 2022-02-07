#pragma once

#include <stdint.h>

struct argp;
struct argp_option;

typedef int argp_callback(struct argp* self, const struct argp_option* option);

enum argp_flag {
    ARGP_STOP_AT_NON_OPTION = 1 << 0,
    ARGP_IGNORE_UNKNOWN_ARGS = 1 << 1,
};

enum argp_option_type {
    ARGP_OPT_END,
    ARGP_OPT_GROUP,
    ARGP_OPT_BOOL,
    ARGP_OPT_BIT,
    ARGP_OPT_INT,
    ARGP_OPT_FLOAT,
    ARGP_OPT_STR,
};

enum argp_option_flags {
    ARGP_OPT_NONEG = 1,
};

struct argp_option {
    enum argp_option_type type;
    const char short_name;
    const char* long_name;
    void* value;
    const char* help;
    argp_callback* callback;
    intptr_t data;
    int flags;
};

struct argp {
    const struct argp_option* options;
    const char* const* usages;
    int flags;
    const char* description;
    const char* epilogue;
    int argc;
    const char** argv;
    const char** out;
    int cp_idx;
    const char* opt_value;
};

int argp_help_cb(struct argp* self, const struct argp_option* option);

#define OPT_END() \
    { ARGP_OPT_END, 0, NULL, NULL, 0, NULL, 0, 0 }
#define OPT_BOOLEAN(...) \
    { ARGP_OPT_BOOLEAN, __VA_ARGS__ }
#define OPT_BIT(...) \
    { ARGP_OPT_BIT, __VA_ARGS__ }
#define OPT_INT(...) \
    { ARGP_OPT_INT, __VA_ARGS__ }
#define OPT_FLOAT(...) \
    { ARGP_OPT_FLOAT, __VA_ARGS__ }
#define OPT_STR(...) \
    { ARGP_OPT_STR, __VA_ARGS__ }
#define OPT_GROUP(h) \
    { ARGP_OPT_GROUP, 0, NULL, NULL, h, NULL, 0, 0 }
#define OPT_HELP() \
    OPT_BOOLEAN('h', "help", NULL, "Show this help message and exit", argp_help_cb, 0, OPT_NONEG)

int argp_init(struct argp* argp, struct argp_option* options, const char* const* usages, int flags);
void argp_describe(struct argp* argp, const char* description, const char* epilogue);
int argp_parse(struct argp* argp, int argc, const char** argv);
void argp_usage(struct argp* argp);
