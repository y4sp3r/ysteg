//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
#include "types.h"

//
#include "const.h"

//
#include "file.h"

//
#include "enc.h"

//
#include "ppm.h"

//
#include "steg.h"

//
int main(int argc, char **argv)
{
  //
  if (argc < 5)
    return printf("Usage: %s -hide [input file] [key file] [input ppm] [output ppm]\n"
		  "       %s -extract [input ppm] [key file] [output file]\n", argv[0], argv[0]), 2;
  
  //
  if (!strcmp(argv[1], "-hide"))
    {
      //
      if (argc < 6)
	return printf("Error: wrong number of command line parameters!\n"), 3;
      
      steg_insert(argv[2], argv[3], argv[4], argv[5]);
    }
  else
    if (!strcmp(argv[1], "-extract"))
      {
	steg_extract(argv[2], argv[3], argv[4]);
      }
    else
      return printf("Error: unknown parameter '%s'!\n", argv[1]), 3;
  
  //
  return 0;
}
