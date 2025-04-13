#ifndef RAND64SW_H
#define RAND64SW_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void software_rand64_init (const char *filename);
unsigned long long software_rand64 (void);
void software_rand64_fini (void);
void software_mrand48_r_init(const char *);
unsigned long long software_mrand48_r(void);
void software_mrand48_r_fini(void);

#endif