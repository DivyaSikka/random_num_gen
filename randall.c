/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "options.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "output.h"

extern char *optarg;
extern int optind; 

void print_help(const char *progname) {
  printf("Usage: %s [-i input] [-o output] N\n", progname);
  printf("  -i input   : Specify input source (rdrand, stdio) [default: rdrand]\n");
  printf("  -o output  : Specify output destination (stdio) [default: stdio]\n");
  printf("  -h         : Show this help message\n");
}

/* Main program, which outputs N bytes of random data.  */
int main (int argc, char **argv)
{
  char *input = "rdrand"; //input
  char *output = "stdio"; //output

  int opt;
  while ((opt = getopt(argc, argv, "i:o:h")) != -1){
    switch(opt){
      case 'i':
        //printf("-i input option\n");
        input = optarg; 
        break;
      case 'o':
        output = optarg;
        break;
      case 'h':
        print_help(argv[0]);
        return 0;
      default:
        print_help(argv[0]);
        return 1;
    }
  }

  //printf("Input: %s\nOutput: %s\n", input, output);

  //returns the number of bytes
  //printf("Calling handle_nbytes\n");
  int nbytes = handle_nbytes(argc, argv);
  if(nbytes == -1){
    printf("nbytes invalid\n");
    return 1;
  }
  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0){
    printf("nbytes 0\n");
    return 0;
  }

  //error handling for rdrand
  if (strcmp(input, "rdrand") == 0) {
    if (!rdrand_supported()) {
        fprintf(stderr, "Error: RDRAND is not supported on this CPU. Use '-i stdio' instead.\n");
        return 1;
      }
    }
  //printf("Calling handle_output\n");
  handle_output(input, output, nbytes);

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  
  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  if (rdrand_supported ())
    {
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
  else
    {
      initialize = software_rand64_init;
      rand64 = software_rand64;
      finalize = software_rand64_fini;
    }

  initialize ();
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
      {
	      output_errno = errno;
	      break;
      }
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }

  finalize ();
  return !!output_errno; */
}
