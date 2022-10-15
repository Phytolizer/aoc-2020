#ifndef STRTOK_REENTRANT_H_
#define STRTOK_REENTRANT_H_

// Copy of glibc strtok_r for use on systems that don't have it.

char* strtok_reentrant(char* str, const char* delim, char** saveptr);

#endif  // STRTOK_REENTRANT_H_
