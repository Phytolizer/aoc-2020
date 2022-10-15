#ifndef SLURP_H_
#define SLURP_H_

typedef struct {
    char* value;
    char* error;
} slurp_result_t;

slurp_result_t slurp_file(const char* path);

#endif  // SLURP_H_
