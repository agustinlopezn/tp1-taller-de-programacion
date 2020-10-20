#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cipher_t {
    size_t idx;
    unsigned int i;
    unsigned int j;
    unsigned char *S;
    char *method;
    unsigned char *key;
}cipher_t;

// Initializes the cipher with its metod and key
// (allocates heap memory if rc4 is the method)
void cipher_init(struct cipher_t *self, char *method, unsigned char *key);

// Encrypts the string with the method and key previously initialized.
// Receives the size of the string, modifies the string and returns it.

unsigned char *cipher_encrypt(struct cipher_t *self,
                              unsigned char *string, size_t size);

// Aplies Caesar cipher into a string, returns the modified string
unsigned char *cipher_caesar(struct cipher_t *self,
                             unsigned char *string, size_t size);
// Decrypts Caesar of a string, returns the modified string
unsigned char *decipher_caesar(struct cipher_t *self,
                               unsigned char *string, size_t size);

// Aplies Vignere cipher with a key into a string, returns the modified string
unsigned char *cipher_vigenere(struct cipher_t *self,
                               unsigned char *string, size_t size);
// Decrypts Vigenere of a string, returns the modified string
unsigned char *decipher_vigenere(struct cipher_t *self,
                                 unsigned char *string, size_t size);

// Aplies RC4 cipher with a key into a string, returns the modified string
unsigned char *cipher_rc4(struct cipher_t *self,
                          unsigned char *string, size_t size);
void init_cipher_rc4(struct cipher_t *self);
// Decrypts Vigenere of a string, returns the modified string
unsigned char *decipher_rc4(struct cipher_t *self,
                            unsigned char *string, size_t size);

// Decrypts the string with the method and key previously initialized.
// Receives the size of the string, modifies it and returns it.
unsigned char *cipher_decrypt(struct cipher_t *self,
                              unsigned char *string, size_t size);

// Frees the keystream if rc4 was used and resets all the structure variables
void cipher_uninit(struct cipher_t *self);
