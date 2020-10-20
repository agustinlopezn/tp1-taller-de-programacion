#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "common_socket.h"


typedef struct client_t {
    socket_t *skt;
    const char *address;
    const char *port;
}client_t;

int client_create(struct client_t *self, const char *port, const char *address);

int client_connect(struct client_t *self);

int client_recv(struct client_t *self);

int client_send(struct client_t *self, unsigned char *message, size_t msg_len);

int client_close(struct client_t *self);

int client_destroy(struct client_t *self);

#endif // CLIENT_Hs
