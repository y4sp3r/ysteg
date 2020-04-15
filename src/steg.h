#ifndef STEG_H
#define STEG_H

//
void insert_file_in_ppm(file_t *f, ppm_t *p);

//
file_t *extract_file_from_ppm(ppm_t *p);

//
void merge_bytes(u8 *data, u64 size, u8 *image);

//
void split_bytes(u8 *image, u8 *data, u64 size);

//
void steg_insert(u8 *ifname, u8 *kfname, u8 *ipfname, u8 *opfname);

//
void steg_extract(u8 *ipfname, u8 *kfname, u8 *ofname);

#endif
