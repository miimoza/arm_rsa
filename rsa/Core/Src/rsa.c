#include <sodium.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHA256_LEN 32

static void print_array(char *name, uint8_t *array, size_t length)
{
    printf("%s:\n", name);
    for (size_t i = 0; i < length; i++)
        printf("%02x", array[i]);
    printf("\n\n");
}

unsigned long long get_encoded_hash(uint8_t *rsa_secret_key, uint8_t *hash, uint8_t *encoded_hash)
{
    unsigned long long encoded_hash_len;

    if (crypto_sign(encoded_hash, &encoded_hash_len, hash, SHA256_LEN, rsa_secret_key) != 0) {
        printf("Can't encore hash with rsa secret key\n");
        return 0;
    }

    return encoded_hash_len;
}

void uart_main(uint8_t *rsa_secret_key, char *passphrase, uint8_t *hash) {
    // check passphrase
    if (strcmp(passphrase, "ronaldo")) {
        printf("Wrong Passphrase!\n");
        return;
    }

    // alloc memory for encoded hash
    uint8_t *encoded_hash = malloc(sizeof(uint8_t) * (SHA256_LEN + crypto_sign_BYTES));
    memset(encoded_hash, '\0', SHA256_LEN);
    size_t encoded_hash_len = get_encoded_hash(rsa_secret_key, hash, encoded_hash);

    // send hash via UART
    print_array("encoded_hash", encoded_hash, encoded_hash_len);

    // end
    free(encoded_hash);
}

// TEST

static uint8_t *generate_rsa_keys()
{
    static uint8_t rsa_secret_key[crypto_sign_SECRETKEYBYTES];
    static uint8_t rsa_public_key[crypto_sign_PUBLICKEYBYTES];

    if (crypto_sign_keypair(rsa_public_key, rsa_secret_key) < 0) {
      printf("Can't create rsa public/secret keys\n");
      return NULL;
    }

    print_array("rsa_secret_key", rsa_secret_key, crypto_sign_SECRETKEYBYTES);
    print_array("rsa_public_key", rsa_public_key, crypto_sign_PUBLICKEYBYTES);

    return rsa_secret_key;
}

int main(int argc, char **argv) {
    (void)argc;
    char *hash_str = argv[1];
    char *password = argv[2];

    printf("hash str: %s | password: %s\n\n", hash_str, password);

    uint8_t *hash = malloc(sizeof(uint8_t) * (SHA256_LEN + crypto_sign_BYTES));
    memset(hash, '\0', SHA256_LEN);
    size_t hlen = strlen(hash_str);
    memcpy(hash, hash_str, hlen);
    print_array("hash hex", hash, SHA256_LEN);

    uint8_t *rsa_secret_key = generate_rsa_keys();
    uart_main(rsa_secret_key, password, hash);

    free(hash);

    return 0;
}
