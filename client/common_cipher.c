#include "common_cipher.h"

#define ASCII_QUAN 256  // Quantity of characters in ascii table

void cipher_init(struct cipher_t *self, char *method, unsigned char *key) {
    self->idx = 0;
    self->method = method;
    self->key = key;
    self->i = 0;
    self->j = 0;
    if (strcmp(method, "rc4") == 0) {
        init_cipher_rc4(self);
    }
}

unsigned char *cipher_encrypt(struct cipher_t *self,
                              unsigned char *string, size_t size) {
    if (strcmp(self->method, "cesar") == 0) {
        return cipher_caesar(self, string, size);
    }
    if (strcmp(self->method, "vigenere") == 0) {
        return cipher_vigenere(self, string, size);
    }
    if (strcmp(self->method, "rc4") == 0) {
        return cipher_rc4(self, string, size);
    }
    return NULL;
}

unsigned char *cipher_caesar(struct cipher_t *self,
                            unsigned char *string, size_t size) {
    unsigned int new_value = 0;
    int n = atoi((char*)self->key);

    for (int i = 0; i < size; i++) {
        new_value = (unsigned int)(string[i] + n) % ASCII_QUAN;
        string[i] = (char)new_value;
    }

    return string;
}

unsigned char *cipher_vigenere(struct cipher_t *self,
                              unsigned char *string, size_t size) {
    size_t key_len = strlen((char*)self->key);
    unsigned int new_value = 0;

    for (size_t i = 0; i < size; i++) {
        new_value = (unsigned int)(string[i] + self->key[self->idx%key_len]);
        string[i] =  (char)(new_value) % ASCII_QUAN;
        self->idx++;
    }

    return string;
}

void swap(unsigned char *string, unsigned int i, unsigned int j) {
    unsigned char aux = string[i];
    string[i] = string[j];
    string[j] = aux;
}

unsigned char *cipher_rc4(struct cipher_t *self,
                        unsigned char *string, size_t string_len) {
    unsigned char key;

    for (size_t idx = 0; idx < string_len; idx++) {
        self->i = (self->i + 1) & (ASCII_QUAN-1);
        self->j = (self->j + self->S[self->i]) & (ASCII_QUAN-1);
        swap(self->S, self->i, self->j);
        key = self->S[(self->S[self->i] + self->S[self->j]) & (ASCII_QUAN-1)];
        string[idx] = key ^ string[idx];
        self->idx++;
    }

    return string;
}


void init_cipher_rc4(struct cipher_t *self) {
    size_t key_len = strlen((char*)self->key);
    self->S = calloc(ASCII_QUAN, sizeof(unsigned char));

    for (unsigned int i = 0; i < ASCII_QUAN; i++) {
        self->S[i] = i;
    }

    // auxiliary to cast easily
    unsigned int key_at_idx = 0;
    unsigned int string_at_idx = 0;
    for (unsigned int i = 0, j = 0; i < ASCII_QUAN; i++) {
        key_at_idx = (unsigned int)self->key[i % key_len];
        string_at_idx = (unsigned int)self->S[i];
        j = (j + string_at_idx + key_at_idx) & (ASCII_QUAN-1);
        swap(self->S, i, j);
    }
}



unsigned char *decipher_caesar(struct cipher_t *self,
                            unsigned char *string) {
    unsigned int new_value = 0;
    int n = atoi((char*)self->key);
    size_t len = strlen((char*)string);

    for (size_t i = 0; i < len; i++) {
        new_value = (unsigned int)(string[i] - n) % ASCII_QUAN;
        string[i] = (char)new_value;
    }

    return string;
}


unsigned char *decipher_vigenere(struct cipher_t *self, unsigned char *string) {
    size_t key_len = strlen((char*)self->key);
    unsigned int new_value = 0;
    size_t len = strlen((char*)string);

    for (size_t i = 0; i < len; i++) {
        new_value = (unsigned int)(string[i] - self->key[self->idx%key_len]);
        string[i] =  (char)(new_value) % ASCII_QUAN;
        self->idx++;
    }

    return string;
}

unsigned char *decipher_rc4(struct cipher_t *self,
                            unsigned char *string, size_t size) {
    return cipher_rc4(self, string, size);
}

unsigned char *cipher_decrypt(struct cipher_t *self,
                              unsigned char *string, size_t size) {
    if (strcmp(self->method, "cesar") == 0) {
        return decipher_caesar(self, string);
    }
    if (strcmp(self->method, "vigenere") == 0) {
        return decipher_vigenere(self, string);
    }
    if (strcmp(self->method, "rc4") == 0) {
        return decipher_rc4(self, string, size);
    }
    return NULL;
}

void cipher_uninit(struct cipher_t *self) {
    self->idx = 0;
     if (strcmp(self->method, "rc4") == 0) {
        free(self->S);
    }
    self->i = 0;
    self->j = 0;
    self->key = NULL;
    self->method = NULL;
}
