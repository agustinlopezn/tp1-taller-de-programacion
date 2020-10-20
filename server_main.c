#include "server.h"
#include "common_connection_util.h"
#include "common_param_parser.h"
#include "common_cipher.h"

#define BLOCK_SIZE 64
#define PORT_POS 1
#define METHOD_POS 2
#define KEY_POS 3
#define DELIM "="

int main(int argc, char *argv[]) {
    struct server_t server;
    struct cipher_t cipher;
    unsigned char buffer[BLOCK_SIZE];
    char *method, *key;
    size_t size;

    parser_get_method(&method, argv[METHOD_POS], DELIM);
    parser_get_key(&key, argv[KEY_POS], DELIM);

    cipher_init(&cipher, method, (unsigned char*)key);
    server_create(&server, argv[PORT_POS]);
    server_connect(&server);
    server_accept(&server);
    memset(buffer, 0, BLOCK_SIZE);
    
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
