#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct flags;

struct flags* flag_init(void);

void flag_int64(struct flags* flags, int64_t* location, const char* name, const char* description);
void flag_str(struct flags* flags, const char** location, const char* name,
              const char* description);
void flag_bool(struct flags* flags, bool* location, const char* name, const char* description);

int flag_parse(struct flags* flags, int argc, char** argv);
void flag_print_help(const struct flags* flags, const char* program_name, FILE* stream);

void flag_free(struct flags* flags);
