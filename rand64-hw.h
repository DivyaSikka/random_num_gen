#ifndef RAND64HW_H
#define RAND64HW_H
#include <cpuid.h>
#include <immintrin.h>
#include <stdbool.h>

void hardware_rand64_init (const char *);
unsigned long long hardware_rand64 (void);
void hardware_rand64_fini (void);
_Bool rdrand_supported (void);

#endif