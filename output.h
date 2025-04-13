#ifndef OUTPUT_H
#define OUTPUT_H
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "rand64-sw.h"
#include "rand64-hw.h"

bool writebytes (unsigned long long x, int nbytes);
int handle_output(char *input, char *output, int nbytes);

#endif