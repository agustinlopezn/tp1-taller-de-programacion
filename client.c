#define _POSIX_C_SOURCE 201112L // Habilita getaddrinfo

#include "client.h"
#include "common_connection_util.h"

#define ERROR_CODE -1

int client_create(struct client_t *self,
                  const char *port, const char *address) {
    self->address = address;
    self->port = port;
    self->skt = calloc(1, sizeof(socket_t));
    if (self->skt) return ERROR_CODE;
    socket_create(self->skt);
    return 1;
}

int client_connect(struct client_t *self) {
    struct addrinfo* info;

    int error = common_get_address_info(self->address, self->port, &info, 0);
    if (error) {
        return ERROR_CODE;
    }
    return socket_start(self->skt, info, false);
}

int client_send(struct client_t *self, unsigned char *string, size_t msg_len) {
    return socket_send(self->skt, string, msg_len);
}

int client_close(struct client_t *self) {
    socket_close(self->skt);
    return 0;
}

void client_destroy(struct client_t *self) {
    socket_destroy(self->skt);
    free(self->skt);
    self->address = NULL;
    self->port = NULL;
}
