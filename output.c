#include "output.h"

bool writebytes (unsigned long long x, int nbytes)
{
  do
    {
      if (putchar (x) < 0)
	      return false;
      x >>= CHAR_BIT;
      nbytes--;
    }
  while (0 < nbytes);

  return true;
}

void writebuffer (unsigned long long x, int outbytes, void* buffer, int index){
  do
    {
      char val = x%256; //LSB
      ((char*)buffer)[index] = val; //adds it to buffer
      x >>= CHAR_BIT;
      index++;
      outbytes--;
    }
  while (0 < outbytes);
}

void handle_n_option(long long int N, int nbytes, unsigned long long int (*rand64)(void)){
  //int output_errno = 0;
  int wordsize = sizeof rand64();
  //allocate nbytes to buffer 
  void* buffer = malloc(nbytes);
  int index = 0;
  int total = nbytes;
  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      writebuffer (x, outbytes, buffer, index); //write to buffer
      nbytes -= outbytes;
      index += outbytes;
    }
    while (0 < nbytes); 
  //now everything is in buffer
  int count_buffer = 0;
  while(count_buffer < total){
    if ((total - count_buffer) < N){
      N = total-count_buffer;
    }
    size_t written = write(1, buffer, N);
    if ((int)written == -1){ //ERROR (couldn't write to buffer)
      exit(EXIT_FAILURE);
    }
    count_buffer += written;
  }
  free(buffer); //free memory
}

int handle_output(char *input, char *output, int nbytes) {
  // Initialize local variables
  void (*initialize)(const char *);
  unsigned long long (*rand64)(void);
  void (*finalize)(void);

  // Error handling for missing input or output
  if(!input || !output){
    return -1;
  }

  // Handle input options
  if (strcmp(input, "rdrand") == 0) {
    // Handles hardware case
    //printf("rdrand case\n");
    initialize = hardware_rand64_init;
    rand64 = hardware_rand64;
    finalize = hardware_rand64_fini;
  } 
  else if (strcmp(input, "mrand48_r") == 0) {
    // Handles lrand48_r case
    initialize = software_mrand48_r_init;
    rand64 = software_mrand48_r;
    finalize = software_mrand48_r_fini;
  } 
  else {
    // Handle /F case, modify software functions for this 
    if (strncmp(input, "/", 1) != 0) {  //Make sure it's an absolute path
      fprintf(stderr, "Error: File name must start with '/'\n");
      exit(EXIT_FAILURE);
    }
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }
  // Initialize random function
  initialize(input);
  int wordsize = sizeof rand64();
  int output_errno = 0;

  if (strcmp(output, "stdio") == 0) {
    // Default stdio option
    //printf("stdio case\n");
    //printf("nbytes: %d", nbytes);
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
  } 
  else {
    // Handle -o N option
    char *endptr;
    long long int N = strtoll (output, &endptr, 10);
    if (endptr == output){ //handle the case of N being a character
      perror ("Invalid input for -o");
      exit(EXIT_FAILURE);
    }
    //printf("N: %llo\n", N);
    handle_n_option(N, nbytes, rand64);
  }

  finalize();
  return output_errno;
}
