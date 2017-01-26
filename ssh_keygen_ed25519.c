/* by pts@fazekas.hu at Thu Jan 26 15:04:16 CET 2017
 *
 * gcc -W -Wall -Wextra -Werror -ffunction-sections -fdata-sections -Wl,--gc-sections -s -Os -o tgen tgen.c
 */

#if __XTINY__
#include <xtiny.h>
#else
#include <string.h>
#include <unistd.h>
#endif

#include "tweetnacl.c"

/* !! xtiny */
#if 0
void randombytes(u8 *a,u64 b) { (void)a; (void)b; }
#endif

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

static void print(const char *msg) {
  (void)!write(1, msg, strlen(msg));
}

static char hextable[16] = "0123456789abcdef";

static void printhex32(const u8 *data, char trailer) {
  u8 buf[65], *p = buf;
  unsigned i;
  for (i = 0; i < 32; ++i) {
    const unsigned char c = data[i];
    *p++ = hextable[c >> 4];
    *p++ = hextable[c & 15];
  }
  *p = trailer;
  (void)!write(1, buf, 65);
}

int main(int argc, char **argv) {
  static const u8 private_key[32]        = "\x79\x20\x22\xc5\x58\xec\x6a\x70\x9c\x68\xac\x10\x90\xb6\xc1\x42\x5d\xa1\x9c\x66\xc7\x15\x64\x61\x8d\xd5\xad\x76\x36\x13\x51\x79";
  static const u8 private_key_hashed[32] = "\x94\x1d\xae\xf5\xdc\x59\xd0\x92\x87\x50\x9c\x73\xa1\x48\x91\x56\x48\x31\x07\x69\xcf\x9f\xe5\x08\x28\x7d\x92\x49\x9d\xbd\x24\x0b";
  static const u8 public_key_exp[32]     = "\x53\xb4\xc6\x18\xdb\x30\x01\xf1\x5a\x52\x9d\xd3\xdc\x86\x62\x87\x17\xb5\x60\x23\x10\xe7\xf3\x5c\x1f\xab\x0f\x69\xde\x61\xd9\x3f";
  u8 public_key[32];

  (void)argc; (void)argv;
  (void)private_key; (void)private_key_hashed;

  my_crypto_sign_ed25519_tweetnacl_keypair(public_key, private_key);

  print("private_key_hashed: "); printhex32(private_key_hashed, '\n');
  print("public_key_exp:     "); printhex32(public_key_exp, '\n');
  print("public_key:         "); printhex32(public_key, '\n');
  return 0;
}
