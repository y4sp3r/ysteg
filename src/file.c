//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <emmintrin.h>

//
#include "types.h"

//
#include "const.h"

//
#include "file.h"

//
file_t *load_file(u8 *fname)
{
  //If valid pointer
  if (fname)
    {
      FILE *fp = fopen(fname, "rb");

      //If file open sucessfully
      if (fp)
	{
	  //Read file size
	  struct stat sb;

	  stat(fname, &sb);

	  u64 size = sb.st_size;

	  //Allocate memory for the file
	  file_t *f = malloc(sizeof(file_t));

	  //If file pointer valid
	  if (f)
	    {
	      //Set file attributes
	      f->size = size;
	      
	      //Allocate aligned memory for file data
	      f->data = _mm_malloc(size, MEM_ALIGN);

	      //If data pointer is valid
	      if (f->data)
		{
		  //Read bytes from file
		  fread(f->data, sizeof(u8), size, fp);

		  //
		  fclose(fp);
		  
		  //Return the pointer address
		  return f;
		}
	      else
		{
		  printf("Error: cannot allocate memory for file data!\n");
		  return NULL;
		}
	    }
	  else
	    {
	      printf("Error: cannot allocate memory for file!\n");
	      return NULL;
	    }
	}
      else
	{
	  printf("Error: cannot open file '%s'\n", fname);
	  return NULL;
	}
    }
  else
    {
      printf("Error: File name pointer is NULL!\n");
      return NULL;
    }
}

//
void dump_file(u8 *fname, file_t *f)
{
  //
  if (fname)
    {
      //
      if (f)
	{
	  //
	  if (f->data)
	    {
	      FILE *fp = fopen(fname, "wb");

	      //
	      if (fp)
		{
		  //
		  fwrite(f->data, sizeof(u8), f->size, fp);
		  
		  //
		  fclose(fp);
		}
	      else
		{
		  printf("Error: cannot open file '%s'\n", fname);
		  exit(1);
		}
	    }
	  else
	    {
	      printf("Error: Data file pointer is NULL!\n");
	      exit(1);
	    }
	}
      else
	{
	  printf("Error: File pointer is NULL!\n");
	  exit(1);
	}
    }
  else
    {
      printf("Error: File name pointer is NULL!\n");
      exit(1);
    }
}

//
file_t *create_file(u64 size)
{
  //
  file_t *f = malloc(sizeof(file_t));

  //
  if (f)
    {
      //
      f->size = size;
      
      //
      f->data = _mm_malloc(size, MEM_ALIGN);

      if (f->data)
	{
	  //
	  memset(f->data, 0, size);
	  
	  return f;
	}
      else
	return NULL;
    }
  else
    return NULL;
}

//Deflate using zlib
void compress_file(file_t *f)
{
}

//Inflate using zlib
void decompress_file(file_t *f)
{
}

//
void destroy_file(file_t **f)
{
  if (*f)
    {
      //
      if ((*f)->data)
	_mm_free((*f)->data);
      
      free(*f);
    }
}
