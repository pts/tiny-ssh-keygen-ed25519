/* by pts@fazekas.hu at Wed Jan 18 16:26:26 CET 2017
 *
 * https://github.com/agl/curve25519-donna/tree/f7837adf95a2c2dcc36233cb02a1fb34081c0c4a
 * See also the README.
 *
 * https://raw.githubusercontent.com/agl/curve25519-donna/f7837adf95a2c2dcc36233cb02a1fb34081c0c4a/curve25519-donna.c
 */

#include <stdint.h>
#include <stdio.h>

#include "tweetnacl.c"

int my_crypto_sign_ed25519_tweetnacl_keypair(unsigned char *pk, const unsigned char *sk) {
    unsigned char h[64];
    gf p[4];

    /* randombytes(sk, 32); */
    crypto_hash(h, sk, 32);
    h[0] &= 248;
    h[31] &= 63;
    h[31] |= 64;

    scalarbase(p, h);
    pack(pk, p);

    return 0;
}


int main(int argc, char **argv) {
  static const uint8_t private_key[32]     = "\x79\x20\x22\xc5\x58\xec\x6a\x70\x9c\x68\xac\x10\x90\xb6\xc1\x42\x5d\xa1\x9c\x66\xc7\x15\x64\x61\x8d\xd5\xad\x76\x36\x13\x51\x79";
  static const uint8_t private_key_hashed[32] = "\x94\x1d\xae\xf5\xdc\x59\xd0\x92\x87\x50\x9c\x73\xa1\x48\x91\x56\x48\x31\x07\x69\xcf\x9f\xe5\x08\x28\x7d\x92\x49\x9d\xbd\x24\x0b";
  static const uint8_t public_key_exp[32]  = "\x53\xb4\xc6\x18\xdb\x30\x01\xf1\x5a\x52\x9d\xd3\xdc\x86\x62\x87\x17\xb5\x60\x23\x10\xe7\xf3\x5c\x1f\xab\x0f\x69\xde\x61\xd9\x3f";
  
  static const uint8_t basepoint[32] = { 9 };
  uint8_t public_key[32];
  unsigned i;

  (void)argc; (void)argv;
  (void)basepoint; (void)private_key; (void)private_key_hashed;

  my_crypto_sign_ed25519_tweetnacl_keypair(public_key, private_key);

  printf("private_key_hashed: "); for (i = 0; i < 32; ++i) printf("%02x", 255 & private_key_hashed[i]); printf("\n");
  printf("public_key_exp:     "); for (i = 0; i < 32; ++i) printf("%02x", 255 & public_key_exp[i]); printf("\n");
  printf("public_key:         "); for (i = 0; i < 32; ++i) printf("%02x", 255 & public_key[i]); printf("\n");
  return 0;
}
