#define  _POSIX_C_SOURCE 200809L
#include "client.h"
#include "common_cipher.h"
#include "common.h"
#include "client_file_reader.h"

#define BLOCK_SIZE 64
#define METHOD_POS 3
#define KEY_POS 4
#define DELIM "="

int main(int argc, char *argv[]) {
    struct client_t client;
    struct cipher_t cipher;
    struct file_reader_t file_reader;
    char *method, *key;

    parser_get_method(&method, argv[METHOD_POS], DELIM);
    parser_get_key(&key, argv[KEY_POS], DELIM);

    file_reader_init(&file_reader, stdin);
    cipher_init(&cipher, method, (unsigned char*)key);
    client_create(&client, argv[2], argv[1]);
    client_connect(&client);

    unsigned char buffer[BLOCK_SIZE];
    size_t size;

    while (!file_reader_finished(&file_reader)) {
        size = file_reader_read(&file_reader, buffer, BLOCK_SIZE);
        if (size < 1) break;
        cipher_encrypt(&cipher, (unsigned char*)buffer, size);
        client_send(&client, (unsigned char*)buffer, size);
    }

    file_reader_uninit(&file_reader);
    cipher_uninit(&cipher);
    client_close(&client);
    client_destroy(&client);
    return 0;
}
