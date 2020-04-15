#ifndef ENC_H
#define ENC_H

//
#include "types.h"

//
#include "file.h"

//
void xor_encrypt_inplace(u8 *in, u8 *key, u64 len);

//
void xor_encrypt(u8 *in, u8 *key, u8 *out, u64 len);

//
void xor_cipher(u8 *ifname, u8 *kfname, u8 *ofname);

//
u8 xor_encrypt_file(file_t *f, file_t *k);

#endif
