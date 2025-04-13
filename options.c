#include "options.h"

long long handle_nbytes(int argc, char **argv){
/* Check arguments.  */
  bool valid = false;
  long long nbytes;
  //printf("argc: %d\n argv[1]: %s\n", argc, argv[1]);
  if (optind >= argc){
    //error
    fprintf(stderr, "Missing argument N\n");
    return 1;
  }

  if (argc >= 2)    
  {   
    //printf("argc >=2\n");
    char *endptr;
    errno = 0;
    nbytes = strtoll (argv[optind], &endptr, 10);
    if (errno)
	    perror (argv[1]);
    else
	    valid = !*endptr && 0 <= nbytes;
  }
  if (!valid)
  {
    fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
    return -1; //invalid (return -1)
  }
    return nbytes;
}

