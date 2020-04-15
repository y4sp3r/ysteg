//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emmintrin.h>

//
#include "types.h"

//
#include "const.h"

//
#include "ppm.h"

//
ppm_t *load_ppm(u8 *fname)
{
  if (fname)
    {
      FILE *fp = fopen(fname, "rb");

      //
      if (fp)
	{
	  //
	  u8 c1, c2;
	  u64 w, h, t;

	  //Read first two format character
	  fscanf(fp, "%c%c\n", &c1, &c2);

	  //Only handle P6 ppm files (binary format)
	  if (c1 == 'P' && c2 == '6')
	    {
	      fscanf(fp, "%llu %llu\n", &w, &h);
	      fscanf(fp, "%llu\n", &t);

	      //
	      ppm_t *p = malloc(sizeof(ppm_t));

	      //
	      if (p)
		{
		  //
		  p->w = w;
		  p->h = h;
		  p->t = t;

		  //
		  p->size = (w * h * 3);
		  
		  p->data = _mm_malloc(p->size, MEM_ALIGN);
		  
		  //
		  if (p->data)
		    {
		      //
		      fread(p->data, sizeof(u8), p->size, fp);
		      
		      //
		      fclose(fp);
		      
		      //
		      return p;
		    }
		  else
		    {
		      printf("Error: cannot allocate memory for ppm file data!\n");
		      return NULL;
		    }
		}
	      else
		{
		  printf("Error: cannot allocate memory for ppm file!\n");
		  return NULL;
		}
	    }
	  else
	    {
	      printf("Error: incompatible ppm file format!\n");
	      return NULL;
	    }
	}
      else
	{
	  printf("Error: cannot open ppm file!\n");
	  return NULL;
	}
    }
  else
    {
      printf("Error: ppm file pointer is NULL!\n");
      return NULL;
    }
}

//
void dump_ppm(u8 *fname, ppm_t *p)
{
  //
  if (fname)
    {
      //
      if (p)
	{
	  //
	  if (p->data)
	    {
	      FILE *fp = fopen(fname, "wb");

	      //
	      if (fp)
		{
		  //Print ppm file header
		  fprintf(fp, "P6\n");
		  fprintf(fp, "%llu %llu\n", p->w, p->h);
		  fprintf(fp, "%llu\n", p->t);
		  
		  //Dump ppm data
		  fwrite(p->data, sizeof(u8), p->size, fp);
		  
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
ppm_t *create_ppm(u64 w, u64 h, u64 t)
{
  //
  ppm_t *p = malloc(sizeof(ppm_t));

  //
  if (p)
    {
      //
      p->w = w;
      p->h = h;
      p->t = t;

      //
      p->size = (w * h * 3);

      //
      p->data = _mm_malloc(p->size, MEM_ALIGN);

      //
      if (p->data)
	{
	  memset(p->data, 0, p->size);
	  
	  return p;
	}
      else
	return NULL;
    }
  else
    return NULL;
}

//
void destroy_ppm(ppm_t **p)
{
  if (*p)
    {
      if ((*p)->data)
	free((*p)->data);

      free(*p);
    }
}
