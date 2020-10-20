#include "server.h"
#include "common.h"
#include "common_cipher.h"

#define BLOCK_SIZE 64
#define METHOD_POS 2
#define KEY_POS 3
#define DELIM "="

int main(int argc, char *argv[]) {
    struct server_t server;
    struct cipher_t cipher;
    unsigned char buffer[BLOCK_SIZE];
    char *method, *key;

    parser_get_method(&method, argv[METHOD_POS], DELIM);
    parser_get_key(&key, argv[KEY_POS], DELIM);

    cipher_init(&cipher, method, (unsigned char*)key);
    server_create(&server, argv[1]);
    server_connect(&server);
    server_accept(&server);
    memset(buffer, 0, BLOCK_SIZE);
    size_t size;
    while (size = server_receive(&server, buffer, BLOCK_SIZE), size > 0) {
        cipher_decrypt(&cipher, buffer, size);
        fprintf(stdout, "%s", buffer);
        memset(buffer, 0, BLOCK_SIZE);
    }
    cipher_decrypt(&cipher, buffer, strlen((char *)buffer));
    fprintf(stdout, "%s", buffer);

    cipher_uninit(&cipher);
    server_close(&server);
    server_destroy(&server);
    return 0;
}
