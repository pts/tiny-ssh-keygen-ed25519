/* by pts@fazekas.hu at Wed Jan 18 16:26:26 CET 2017
 *
 * https://github.com/agl/curve25519-donna/tree/f7837adf95a2c2dcc36233cb02a1fb34081c0c4a
 * See also the README.
 *
 * https://raw.githubusercontent.com/agl/curve25519-donna/f7837adf95a2c2dcc36233cb02a1fb34081c0c4a/curve25519-donna.c
 */

#include <stdint.h>
#include <stdio.h>

extern int curve25519_donna(uint8_t *public_key,
                            const uint8_t *private_key_hashed,
                            const uint8_t *basepoint);

/* Wrong primitive, same as curve25519_donna. */
/* extern int crypto_scalarmult_curve25519_tinynacl_base(unsigned char *q, const unsigned char *n); */

extern int crypto_hash_sha512_tinynacl(unsigned char *, const unsigned char *, unsigned long long);
extern void cleanup_(void *, long long);
#define cleanup(x) cleanup_((x), sizeof(x))
typedef uint32_t fe[8];
typedef fe ge25519[4];          /* X, Y, Z, T */
extern void ge25519_scalarmult_base(ge25519, const unsigned char *);
extern void ge25519_tobytes(unsigned char *, ge25519);

int my_crypto_sign_ed25519_tinynacl_keypair(unsigned char *pk, const unsigned char *sk) {
    unsigned char h[64];
    ge25519 A;

    /* randombytes(sk, 32); */
    crypto_hash_sha512_tinynacl(h, sk, 32);
    h[0] &= 248;
    h[31] &= 63;
    h[31] |= 64;

    ge25519_scalarmult_base(A, h);
    ge25519_tobytes(pk, A);

    /* for (i = 31; i >= 0; --i) sk[i + 32] = pk[i]; */
    cleanup(h); cleanup(A);
    return 0;
}


extern int crypto_sign_ed25519_tinynacl_keypair(unsigned char *pk, unsigned char *sk);


int main(int argc, char **argv) {
#if 1
  static const uint8_t private_key[32]     = "\x79\x20\x22\xc5\x58\xec\x6a\x70\x9c\x68\xac\x10\x90\xb6\xc1\x42\x5d\xa1\x9c\x66\xc7\x15\x64\x61\x8d\xd5\xad\x76\x36\x13\x51\x79";
/*  static const uint8_t private_key_hashed[32] = "\x48\x6d\x85\x69\x46\xe6\x19\xf3\xe0\xc3\x7a\xff\x1b\x30\x0d\xaa\x48\x31\x07\x69\xcf\x9f\xe5\x08\x28\x7d\x92\x49\x9d\xbd\x24\x4b"; */
  static const uint8_t private_key_hashed[32] = "\x94\x1d\xae\xf5\xdc\x59\xd0\x92\x87\x50\x9c\x73\xa1\x48\x91\x56\x48\x31\x07\x69\xcf\x9f\xe5\x08\x28\x7d\x92\x49\x9d\xbd\x24\x0b";
  static const uint8_t public_key_exp[32]  = "\x53\xb4\xc6\x18\xdb\x30\x01\xf1\x5a\x52\x9d\xd3\xdc\x86\x62\x87\x17\xb5\x60\x23\x10\xe7\xf3\x5c\x1f\xab\x0f\x69\xde\x61\xd9\x3f";
#endif
#if 0   /* id_tinytest2 */
  static const uint8_t private_key[32] = { 0 };
  static const uint8_t private_key_hashed[32] = "\x68\xf0\xa0\x44\x89\x25\x66\xfe\xc4\x51\xa4\x06\x7c\xc5\x9d\xb6\x64\x2f\x9d\x7c\xd2\xb3\xf7\xe0\x42\x5d\x3e\x71\xe5\x76\xf8\x6c";
  static const uint8_t public_key_exp[32] = "\x89\x58\xfe\x06\xa4\x59\x2e\xaa\xb6\x29\x81\x82\x82\x16\x41\x64\xc5\x9d\xb9\xd6\x72\x44\xe9\x57\xc9\x59\xfe\xb4\x55\xd5\x83\x99";
#endif
  
  static const uint8_t basepoint[32] = { 9 };
  uint8_t public_key[32];
  unsigned i;

  (void)argc; (void)argv;
  (void)basepoint; (void)private_key; (void)private_key_hashed;

#if 0
  curve25519_donna(public_key, private_key_hashed, basepoint);
#endif
#if 0
  crypto_scalarmult_curve25519_tinynacl_base(public_key, private_key_hashed);
#endif
#if 1
  my_crypto_sign_ed25519_tinynacl_keypair(public_key, private_key);
#endif

  printf("private_key_hashed: "); for (i = 0; i < 32; ++i) printf("%02x", 255 & private_key_hashed[i]); printf("\n");
  printf("public_key_exp:     "); for (i = 0; i < 32; ++i) printf("%02x", 255 & public_key_exp[i]); printf("\n");
  printf("public_key:         "); for (i = 0; i < 32; ++i) printf("%02x", 255 & public_key[i]); printf("\n");
  return 0;
}
