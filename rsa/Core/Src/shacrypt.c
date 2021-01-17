#include "rsa.h"
#include "shacrypt.h"
#include "main.h"
#include "mbedtls.h"
#include "hmac_drbg.h"
#include "pk.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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

    mbedtls_rsa_context rsa_cont;
    mbedtls_hmac_drbg_context cont;

    mbedtls_hmac_drbg_init(&cont);
    mbedtls_rsa_init(&rsa_cont, MBEDTLS_RSA_PKCS_V15, 0);

    mbedtls_pk_parse_key(&rsa_cont, PRIVATE_KEY, PRIVATE_KEY_LEN, "", 0);

    int error = mbedtls_rsa_rsassa_pkcs1_v15_sign(&rsa_cont, mbedtls_hmac_drbg_random, &cont,
      MBEDTLS_RSA_PRIVATE, MBEDTLS_MD_SHA256, 300, hash, encoded_hash);

    // ) (encoded_hash, &encoded_hash_len, hash, SHA256_LEN, rsa_secret_key) != 0

    if (error) {
        printf("Can't encore hash with rsa secret key\n");
        return 0;
    }

    return encoded_hash_len;
}

uint8_t *get_secret_key()
{
  static uint8_t secret_key[] = {125, 158, 135, 228, 233, 4, 226, 13, 107, 93,
                                 10, 153, 9, 112, 202, 6, 43, 169, 200, 118, 36,
                                 40, 244, 143, 190, 205, 195, 0, 44, 234, 29,
                                 97, 66, 175, 221, 238, 116, 221, 102, 4, 116,
                                 40, 103, 103, 88, 89, 206, 241, 230, 137, 206,
                                 95, 185, 29, 102, 91, 59, 45, 140, 47, 147,
                                 128, 95, 195};


  return secret_key;
}

unsigned long long uart_main(uint8_t *rsa_secret_key, char *passphrase, uint8_t *hash, uint8_t *encoded_hash) {
    // check passphrase
    if (strcmp(passphrase, "ronaldo")) {
        printf("Wrong Passphrase!\n");
        return;
    }

    // alloc memory for encoded hash
    size_t encoded_hash_len = get_encoded_hash(rsa_secret_key, hash, encoded_hash);

    // send hash via UART
    print_array("encoded_hash", encoded_hash, encoded_hash_len);


    return encoded_hash_len;
}

// TEST

/*
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
}*/

int rsa_wrapper(UART_HandleTypeDef *huart2) {
  char data[10];
  char data1[] = "CACA\n";
  char data2[] = "PIPI\n";

  uint8_t *secret_key = get_secret_key();

  uint8_t *hash = malloc(sizeof(uint8_t) * (SHA256_LEN));
  memset(hash, 23, SHA256_LEN);
  uint8_t *encoded_hash = malloc(sizeof(uint8_t) * (SHA256_LEN + 1024));
  memset(encoded_hash, '\0', SHA256_LEN);

  unsigned long long encoded_hash_len = uart_main(secret_key,"ronaldo", hash, encoded_hash);
  if (encoded_hash_len > 0)
  {
    HAL_UART_Transmit(&huart2, "size > 0", 10, 1000);
    HAL_UART_Transmit(&huart2, encoded_hash, encoded_hash_len, 1000);
  }
  else
  {
    HAL_UART_Transmit(&huart2, "size == 0", 10, 1000);
  }

  /* USER CODE BEGIN 3 */
  HAL_UART_Receive(&huart2, data, 10, 1000);
  HAL_UART_Transmit(&huart2, data1, 10, 1000);

  if (strlen(data) > 0)
  {
    HAL_UART_Transmit(&huart2, data, 10, 1000);
    data[0]=0;
  }

  free(hash);
  free(encoded_hash);
}
