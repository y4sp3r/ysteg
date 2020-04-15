//
#include <stdio.h>
#include <stdlib.h>

//
#include "types.h"

//
#include "file.h"

//Inplace encryption
void xor_encrypt_inplace(u8 *in, u8 *key, u64 len)
{
  for (u64 i = 0; i < len; i++)
    in[i] ^= key[i];
}

//
void xor_encrypt(u8 *in, u8 *key, u64 *out, u64 len)
{
  for (u64 i = 0; i < len; i++)
    out[i] = in[i] ^ key[i];
}

//
u8 xor_encrypt_file(file_t *f, file_t *k)
{
  //
  if (k->size < f->size)
    return 0;

  //
  xor_encrypt_inplace(f->data, k->data, f->size);

  //
  return 1;
}

//
void xor_cipher(u8 *ifname, u8 *kfname, u8 *ofname)
{
    //
  file_t *inf  = load_file(ifname);
  file_t *keyf = load_file(kfname);

  //Key must be of same length than data
  if (keyf->size < inf->size)
    {
      printf("Error: key file size smaller than input file size!\n");
      exit(1);
    }
  
  xor_encrypt_inplace(inf->data, keyf->data, inf->size); 

  //
  dump_file(ofname, inf);
  
  //
  destroy_file(&inf);
  destroy_file(&keyf);
}
