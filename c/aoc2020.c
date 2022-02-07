#include <inttypes.h>
#include <stdlib.h>

#include "simple_flags.h"

int main(int argc, char** argv) {
    struct flags* flags = flag_init();
    int64_t day = 0;
    const char* input_file_path = "input.txt";
    flag_int64(flags, &day, "day", "Set the day to run");
    flag_str(flags, &input_file_path, "input-path", "Set the path to the input file to read");
    int endp = flag_parse(flags, argc, argv);
    if (endp < argc) {
        flag_print_help(flags, argv[0], stderr);
        fprintf(stderr, "ERROR: found dangling arguments, starting with '%s'\n", argv[endp]);
        return EXIT_FAILURE;
    }
    flag_free(flags);

    printf("Day selected: %" PRId64 "\n", day);
    printf("Input file to be used: %s\n", input_file_path);
    return 0;
}
