#ifndef SERVER_H
#define SERVER_H

#include "common_socket.h"

typedef struct server_t {
    socket_t *skt, *client_skt;
    const char *port;
}server_t;

// Creates the server and its sockets
int server_create(struct server_t *self, const char *port);

// Connects the server to its port
int server_connect(struct server_t *self);

// Accepts the conection of its client
int server_accept(struct server_t *self);

// The server receives a buffer from its client
int server_receive(struct server_t *self, unsigned char *buffer, size_t size);

// Closes the sockets of the server
int server_close(struct server_t *self);

// Destroys the sockets and puts the port back to NULL
int server_destroy(struct server_t *self);

#endif // SERVER_H