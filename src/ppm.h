#ifndef PPM_H
#define PPM_H

//
typedef struct ppm_s {

  //Image width
  u64 w;

  //Imahe height
  u64 h;

  //Color threshold
  u64 t;

  //Total size in bytes (w * h * 3)
  u64 size;
  
  //RGB byte stream
  u8 *data;
  
} ppm_t;

//
ppm_t *load_ppm(u8 *fname);

//
void dump_ppm(u8 *fname, ppm_t *p);

//
ppm_t *create_ppm(u64 w, u64 h, u64 t);

//
void destroy_ppm(ppm_t **p);

#endif
