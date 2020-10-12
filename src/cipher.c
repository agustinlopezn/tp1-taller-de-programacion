#include <stdio.h>
#include <string.h>

#define ASCII_QUAN 256  // Quantity of characters in ascii table

char *cipher_caesar(char *string, int n) {
    unsigned int new_value = 0;

    for (int i = 0; i < strlen(string); i++) {
        new_value = (unsigned int)(string[i] + n) % ASCII_QUAN;
        string[i] = (char)new_value;
    }

    return string;
}

char *cipher_vignere(char *string, char *key) {
    size_t key_len = strlen(key);
    size_t key_idx = 0;
    unsigned int new_value = 0;

    for (size_t i = 0; i < strlen(string); i++) {
        key_idx = i % key_len;
        new_value = (unsigned int)(string[i] + key[key_idx]) % ASCII_QUAN;
        string[i] =  (char)new_value;
        }

    return string;
}

void swap(unsigned char *string, unsigned int i, unsigned int j) {
    unsigned char aux = string[i];
    string[i] = string[j];
    string[j] = aux;
}
char *rc4_output(char *string, unsigned char *S, size_t string_len) {
    unsigned int i = 0, j = 0;
    unsigned int string_at_idx = 0;
    
    for (size_t idx = 0; idx < string_len; idx++) {
        i = (i + 1) & (ASCII_QUAN-1);
        string_at_idx = (unsigned int)S[i];
        j = (j + string_at_idx) & (ASCII_QUAN-1);
        swap(S, i, j);
        string[idx] = (char)(S[(S[i] + S[j]) & (ASCII_QUAN-1)]) ^ string[idx];
    }

    return string;
}


char *cipher_rc4(char *string, char *key) {
    unsigned char S[ASCII_QUAN];
    size_t key_len = strlen(key);
    size_t string_len = strlen(string);

    for (unsigned int i = 0; i < ASCII_QUAN; i++) {
        S[i] =  (unsigned char)i;
    }
    // auxiliary to cast easily
    unsigned int key_at_idx = 0;
    unsigned int string_at_idx = 0;
    for (unsigned int i = 0, j = 0; i < ASCII_QUAN; i++) {
        key_at_idx = (unsigned int)key[i % key_len];
        string_at_idx = (unsigned int)S[i];
        j = (j + string_at_idx + key_at_idx) & (ASCII_QUAN-1);
        swap(S, i, j);
    }

    return rc4_output(string, S, string_len);
}