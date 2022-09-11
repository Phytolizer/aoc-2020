#pragma once

typedef struct {
    char* value;
    char* error;
} slurp_result_t;

slurp_result_t slurp_file(const char* path);
