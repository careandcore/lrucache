#ifndef _LEAK_DETECTOR_H
#define _LEAK_DETECTOR_H

#include <malloc.h>
#include <stdio.h>
#define MALLOC(n) mallocEX(n, __FILE__, __LINE__)
#define FREE(p) freeEX(p)

void* mallocEX(size_t n, const char* file, const int line);
void freeEX(void* p);
void PRINT_LEAK_INFO();

#endif