#include <sodium.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHA256_LEN 32





uint8_t *generate_rsa_keys()
{
    uint8_t *rsa_secret_key = malloc(sizeof(uint8_t) * crypto_sign_SECRETKEYBYTES);
    uint8_t *rsa_public_key = malloc(sizeof(uint8_t) * crypto_sign_PUBLICKEYBYTES);

    if (crypto_sign_keypair(rsa_public_key, rsa_secret_key) < 0)
    {
      printf("Can't create rsa public/secret keys\n");
      return NULL;
    }

    printf("rsa_secret_key:%s\n", rsa_secret_key);
    printf("rsa_public_key:%s\n", rsa_public_key);

    return rsa_secret_key;
}

uint8_t *get_encoded_hash(char *hash, char *password, uint8_t *rsa_secret_key)
{
    if (strcmp(password, "ronaldo"))
    {
        printf("Wrong Password!\n");
        return NULL;
    }

    uint8_t *m = malloc(sizeof(uint8_t) * (SHA256_LEN + crypto_sign_BYTES));
    memset(m, '\0', SHA256_LEN);
    uint8_t *encoded_hash = malloc(sizeof(uint8_t) * (SHA256_LEN + crypto_sign_BYTES));
    memset(encoded_hash, '\0', SHA256_LEN);

    unsigned long long mlen = strlen(hash);
    unsigned long long encoded_hash_len;

    memcpy(m, hash, mlen);

    if (crypto_sign(encoded_hash, &encoded_hash_len, m, mlen, rsa_secret_key) != 0)
    {
      printf("Can't encore hash with rsa secret key\n");
      return NULL;
    }

    printf("Encoded Message:%s\n", encoded_hash);
    printf("new size : %llu\n", encoded_hash_len);

    return encoded_hash;
}

int main(int argc, char **argv) {

    char *hash = argv[1];
    char *password = argv[2];

    printf("hash:%s | password:%s\n", hash, password);

    uint8_t *rsa_secret_key = generate_rsa_keys();
    printf("rsa_secret_key:%s\n", rsa_secret_key);

    uint8_t *encoded_hash = get_encoded_hash(hash, password, rsa_secret_key);
    printf("encoded_hash: %s\n", encoded_hash);

    return 0;
}
