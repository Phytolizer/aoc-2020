#pragma once

// Copy of glibc strtok_r for use on systems that don't have it.

char* strtok_reentrant(char* str, const char* delim, char** saveptr);
