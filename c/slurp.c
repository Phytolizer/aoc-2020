#include "slurp.h"

#include <stdbool.h>
#include <stdlib.h>

#include "alloc_printf.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

typedef struct {
#ifdef _WIN32
    HANDLE handle;
#else
    int fd;
#endif
    bool valid;
} platform_file_t;

static platform_file_t platform_fopen(const char* path) {
#ifdef _WIN32
    HANDLE handle = CreateFileA(
        path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
    );
    return (platform_file){
        .handle = handle,
        .valid = handle != INVALID_HANDLE_VALUE,
    };
#else
    int fd = open(path, O_RDONLY);
    return (platform_file_t){.fd = fd, .valid = fd != -1};
#endif
}

static void platform_fclose(platform_file_t file) {
    if (file.valid) {
#ifdef _WIN32
        CloseHandle(file.handle);
#else
        close(file.fd);
#endif
    }
}

static size_t platform_filelen(platform_file_t f) {
#ifdef _WIN32
    LARGE_INTEGER size;
    GetFileSizeEx(f.handle, &size);
    return (size_t)size.QuadPart;
#else
    struct stat st;
    fstat(f.fd, &st);
    return (size_t)st.st_size;
#endif
}

static size_t platform_fread(platform_file_t f, char* buf, size_t len) {
#ifdef _WIN32
    DWORD read;
    ReadFile(f.handle, buf, (DWORD)len, &read, NULL);
    return (size_t)read;
#else
    return (size_t)read(f.fd, buf, len);
#endif
}

slurp_result_t slurp_file(const char* filename) {
    platform_file_t f = platform_fopen(filename);
    if (!f.valid) {
        char* msg = alloc_printf("failed to open '%s' for reading", filename);
        return (slurp_result_t){.error = msg};
    }

    size_t len = platform_filelen(f);

    char* buf = malloc(len + 1);
    if (buf == NULL) {
        platform_fclose(f);
        char* msg = alloc_printf("failed to allocate memory for '%s' contents", filename);
        return (slurp_result_t){.error = msg};
    }

    size_t read = platform_fread(f, buf, len);
    if (read != len) {
        platform_fclose(f);
        free(buf);
        char* msg = alloc_printf("failed to read '%s' contents", filename);
        return (slurp_result_t){.error = msg};
    }

    buf[len] = '\0';

    platform_fclose(f);

    return (slurp_result_t){.value = buf};
}
