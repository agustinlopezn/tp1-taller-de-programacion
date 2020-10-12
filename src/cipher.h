#include <string.h>

// Aplies Caesar cipher into a string
char *cipher_caesar(char *string, int n);
// Aplies Vignere cipher with a key into a string
char *cipher_vignere(char *string, char *key);
// Aplies RC4 cipher with a key into a string
char *cipher_rc4(char *string, char *key);
