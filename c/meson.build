project(
    'aoc2020',
    'c',
    version: '0.1.0',
    default_options: [
        'warning_level=3',
        'default_library=static',
        'c_std=c99',
    ],
)

hedley_proj = subproject('hedley')
hedley_dep = hedley_proj.get_variable('hedley_dep')

executable(
    'aoc2020',
    'aoc2020.c',
    'alloc_printf.c',
    'simple_flags.c',
    'slurp.c',
    'strdup_std.c',
    'strtok_reentrant.c',
    'day01.c',
    'day02.c',
    'day03.c',
    dependencies: [
        hedley_dep,
    ],
)
