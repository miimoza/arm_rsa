#include <sodium.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHA256_LEN 32

int main(void) {
  uint8_t sk[crypto_sign_SECRETKEYBYTES];
  uint8_t pk[crypto_sign_PUBLICKEYBYTES];
  if (crypto_sign_keypair(pk, sk) < 0)
    return 1;

  uint8_t m[SHA256_LEN + crypto_sign_BYTES];
  memset(m, '\0', SHA256_LEN);
  uint8_t sm[SHA256_LEN + crypto_sign_BYTES];
  memset(sm, '\0', SHA256_LEN);

  char *mess = "Hello World!";
  unsigned long long mlen = 13;
  unsigned long long smlen;

  memcpy(m, mess, mlen);

  if (crypto_sign(sm, &smlen, m, mlen, sk) != 0)
    return 1;

  printf("new size : %llu\n", smlen);
  return 0;
}
