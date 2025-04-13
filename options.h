#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern int optind;
long long handle_nbytes(int argc, char **argv);

#endif