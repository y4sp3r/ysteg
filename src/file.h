#ifndef FILE_H
#define FILE_H

//
#include "types.h"

//
typedef struct file_s {

  //Buffer size in bytes
  u64 size;

  //Buffer data/byte stream
  u8 *data;
    
} file_t;

//
file_t *load_file(u8 *fname);

//
void dump_file(u8 *fname, file_t *f);

//
file_t *create_file(u64 size);

//
void compress_file(file_t *f);

//
void decompress_file(file_t *f);

//
void destroy_file(file_t **f);

#endif
