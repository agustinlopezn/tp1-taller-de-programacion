#define _POSIX_C_SOURCE 201112L  // Habilita getaddrinfo
#include "common.h"
#include "server.h"
#include <stdlib.h>
#include <string.h>

#define ACCEPT_QUEUE_LEN 10
#define SERVER_FLAG AI_PASSIVE
#define ERROR_CODE -1

int server_create(struct server_t *self, const char *port) {
    self->port = port;
    self->skt = calloc(1, sizeof(socket_t));
    self->client_skt = calloc(1, sizeof(socket_t));
    socket_create(self->skt);
    socket_create(self->client_skt);
    return 0;
}

int server_connect(struct server_t *self) {
    struct addrinfo *info;

    int error = common_get_address_info(NULL, self->port, &info, SERVER_FLAG);
    if (error) {
        return ERROR_CODE;
    }
    socket_start(self->skt, info, true);

    return 0;
}

int server_accept(struct server_t *self) {
    return socket_accept(self->skt, self->client_skt);
}

int server_receive(struct server_t *self, unsigned char *buffer, size_t size) {
    return socket_receive(self->client_skt, buffer, size);
}

int server_close(struct server_t *self) {
    socket_close(self->skt);
    return socket_close(self->client_skt);  // FIXME
}

int server_destroy(struct server_t *self) {
    self->port = NULL;
    socket_destroy(self->skt);
    socket_destroy(self->client_skt);
    free(self->skt);
    free(self->client_skt);
    return 0;
}