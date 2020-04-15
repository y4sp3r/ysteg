//
#include <stdio.h>
#include <stdlib.h>

//
#include "file.h"

#include "ppm.h"

#include "enc.h"

//
void merge_bytes(u8 *data, u64 size, u8 *image)
{
  //Split each byte into 4 couples and insert each couple
  //as the lower two bits of an image byte
  for (u64 i = 0, j = 0; i < size; i++, j += 4)
    {
      //Extract the bits
      u8 b0 =  data[i] & 0x03; 
      u8 b1 = (data[i] & 0x0C) >> 2; //
      u8 b2 = (data[i] & 0x30) >> 4; //
      u8 b3 = (data[i] & 0xC0) >> 6; //

      //Zero up the last two bits of the taget byte
      image[j] &= 0xFC;
      image[j] |= b0;
      
      image[j + 1] &= 0xFC;
      image[j + 1] |= b1;

      image[j + 2] &= 0xFC;
      image[j + 2] |= b2;

      image[j + 3] &= 0xFC;
      image[j + 3] |= b3;
    }
}

//
void split_bytes(u8 *image, u8 *data, u64 size)
{
  //Extract the lower two bits of each byte and merge them
  //as a byte
  for (u64 i = 0, j = 0; i < size; i++, j += 4)
    {
      //Extract couple
      u8 b0 = image[j] & 0x03;
      u8 b1 = (image[j + 1] & 0x03) << 2;
      u8 b2 = (image[j + 2] & 0x03) << 4;
      u8 b3 = (image[j + 3] & 0x03) << 6;

      //Merge into a byte
      data[i] = (b3 | b2 | b1 | b0);
    }
}		   

//
void insert_file_in_ppm(file_t *f, ppm_t *p)
{
  //Make sure the image has enough size
  //to hold the file data + the size of the file
  if (((f->size << 2) + 8) > p->size)
    {
      printf("Error: ppm image too small!\n");
      exit(1);
    }

  //
  u8 *f_size = (u8 *)&f->size;

  //Insert size (B bytes or 64 bits) in the first 32 bytes of the image 
  merge_bytes(f_size, 8, p->data);

  //Insert the file data starting from the 32nd byte of the image
  merge_bytes(f->data, f->size, p->data + 32);
}

//
file_t *extract_file_from_ppm(ppm_t *p)
{
  u64 f_size;
  
  //Insert size
  split_bytes(p->data, (u8 *)&f_size, 8);

  file_t *f = create_file(f_size);

  if (f)
    {
      split_bytes(p->data + 32, f->data, f_size);
      
      return f;
    }
  else
    return NULL;
}

//
void steg_insert(u8 *ifname, u8 *kfname, u8 *ipfname, u8 *opfname)
{
  //
  file_t *fkey = NULL;
  
  //
  file_t *fin  = load_file(ifname);

  //If fkey not NULL
  if (kfname)
    {
      fkey = load_file(kfname);

      if (!fkey)
	exit(1);
    }
  
  //
  ppm_t *pin   = load_ppm(ipfname);

  //Exit on error
  if (!fin)
    exit(1);
  
  if (!pin)
    exit(1);

  //Encrypt before insertion
  if (kfname)
    if (!xor_encrypt_file(fin, fkey))
      printf("Warning: no encryption performed (key file smaller than file size)!\n");
  
  //
  insert_file_in_ppm(fin, pin);

  //
  dump_ppm(opfname, pin);

  //
  destroy_ppm(&pin);
  destroy_file(&fkey);
  destroy_file(&fin);
}

//
void steg_extract(u8 *ipfname, u8 *kfname, u8 *ofname)
{
  //
  ppm_t *pin = load_ppm(ipfname);
  
  //
  if (!pin)
    exit(1);

  //
  file_t *fout = extract_file_from_ppm(pin);
  
  //Exit on error
  if (!fout)
    exit(1);

  //
  file_t *fkey = NULL;

  //
  if (kfname)
    {
      fkey = load_file(kfname);
      
      if (!fkey)
	exit(1);

      if (!xor_encrypt_file(fout, fkey))
	printf("Warning: no encryption performed (key file smaller than file size)!\n");
    }
  
  //
  dump_file(ofname, fout);
  
  //
  destroy_ppm(&pin);
  destroy_file(&fout);
}

