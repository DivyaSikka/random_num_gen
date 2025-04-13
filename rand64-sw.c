#include "rand64-sw.h"

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;
struct drand48_data state;

/* Initialize the software mrand48_r implementation. */
void software_mrand48_r_init(const char *){
  srand48_r(time(NULL), &state);
}

/* Return a random value, using mrand48_r operations.  */
unsigned long long software_mrand48_r(void){
  long int long1, long2;
  mrand48_r(&state, &long1);
  mrand48_r(&state, &long2);

  //combine the two by shifting long1 to the upper 32 bits and oring with long2 (lower 32 bits)
  unsigned long long rand_value = ((unsigned long long)long1 << 32) | long2;
  return rand_value;
}

void software_mrand48_r_fini(void){
  //nothing needed 
}


/* Initialize the software rand64 implementation.  */
void
software_rand64_init (const char *filename)
{
  if (filename) {  //If a file name is provided
    urandstream = fopen(filename, "r");
  } 
  else {
    urandstream = fopen("/dev/random", "r");
  }

  if (!urandstream) {
    perror("Error opening random source file");
    exit(EXIT_FAILURE);
  }
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  //printf("Random value %llu\n", x);
  return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
} 