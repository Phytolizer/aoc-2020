#include <inttypes.h>
#include <stdlib.h>

#include "day01.h"
#include "day02.h"
#include "simple_flags.h"

int main(int argc, char** argv) {
    struct flags* flags = flag_init();
    int64_t day = 0;
    const char* input_file_path = "input.txt";
    bool help = false;
    flag_int64(flags, &day, "day", "Set the day to run");
    flag_str(flags, &input_file_path, "input-path", "Set the path to the input file to read");
    flag_bool(flags, &help, "help", "Print this help message");
    int endp = flag_parse(flags, argc, argv);
    if (endp < argc) {
        flag_print_help(flags, argv[0], stderr);
        fprintf(stderr, "ERROR: found dangling arguments, starting with '%s'\n", argv[endp]);
        flag_free(flags);
        return EXIT_FAILURE;
    }
    if (help) {
        flag_print_help(flags, argv[0], stdout);
        flag_free(flags);
        return EXIT_SUCCESS;
    }

    if (day == 0) {
        flag_print_help(flags, argv[0], stderr);
        fprintf(stderr, "ERROR: day must be set\n");
        flag_free(flags);
        return EXIT_FAILURE;
    }
    if (day < 0 || day > 25) {
        flag_print_help(flags, argv[0], stderr);
        fprintf(stderr, "ERROR: day must be between 1 and 25\n");
        flag_free(flags);
        return EXIT_FAILURE;
    }
    flag_free(flags);

    printf("Day selected: %" PRId64 "\n", day);
    printf("Input file to be used: %s\n", input_file_path);

    switch (day) {
        case 1:
            return day01(input_file_path);
        case 2:
            return day02(input_file_path);
        default:
            fprintf(stderr, "ERROR: day %" PRId64 " is not implemented\n", day);
            return EXIT_FAILURE;
    }
    return 0;
}
