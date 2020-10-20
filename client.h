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

// Creates the client, initializing the adrress and the port pointers.
// Allocates heap memory for the socket
int client_create(struct client_t *self, const char *port, const char *address);

//Connect the socket of the client, first getting the address info
int client_connect(struct client_t *self);

// Sends a string by the socket.
int client_send(struct client_t *self, unsigned char *string, size_t msg_len);

// Closes the socket of the client
int client_close(struct client_t *self);

// Destroys the socket, asigns NULL to address and port
// and frees the allocated memory in client_create() 
void client_destroy(struct client_t *self);

#endif // CLIENT_Hs
