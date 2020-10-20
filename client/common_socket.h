#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

typedef struct socket_t {
    int fd;
}socket_t;

struct addrinfo;

// Creates the socket with its defaults values
int socket_create(socket_t *self);

// Starts the socket, binds it and puts it in listen mode if the boolean
// is_server is true, otherwise connects it to the address.
int socket_start(socket_t *self, struct addrinfo *info, bool is_server);

// Accepts the conection and asigns it to the client fd
int socket_accept(struct socket_t *host, struct socket_t *client);

// Sends a message to the socket
int socket_send(struct socket_t *self, unsigned char *message, size_t msg_len);

// The socket receives a message comming from the connected socket
int socket_receive(struct socket_t *self,
                unsigned char *buffer, size_t buffer_size);

// Closes the socket from both endpoints(RD and WR)
int socket_close(struct socket_t *self);

// Destroys the socket information
int socket_destroy(struct socket_t *self);
