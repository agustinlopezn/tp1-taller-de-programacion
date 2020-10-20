#define _POSIX_C_SOURCE 201112L // Habilita getaddrinfo

#include "common_socket.h"

#define ERROR_CODE -1

int socket_create(struct socket_t *self) {
    self->fd = -1;
    return 0;
}

int socket_connect(struct socket_t *self, struct addrinfo *info) {
    struct addrinfo *addr;
    int connection_status;

    for (addr = info; addr != NULL; addr = addr->ai_next) {
        self->fd = socket(addr->ai_family,
                        addr->ai_socktype, addr->ai_protocol);
        if (self->fd != -1) {
            connection_status = connect(self->fd,
                                addr->ai_addr, addr->ai_addrlen);
            if (connection_status == 0) {
                return 0;
            }
            fprintf(stderr, "Connection failure: %s\n", strerror(errno));
        }
    }

    return ERROR_CODE;
}

int socket_bind_listen(struct socket_t *self, struct addrinfo *info) {
    struct addrinfo *addr;
    int bind_status;

    for (addr = info; addr != NULL; addr = addr->ai_next) {
        self->fd = socket(addr->ai_family,
                        addr->ai_socktype, addr->ai_protocol);
        if (self->fd != -1) {
            bind_status = bind(self->fd, addr->ai_addr, addr->ai_addrlen);
            if (bind_status == 0 && listen(self->fd, 1) == 0) {
                return 0;
            } else if (bind_status == -1) {
                fprintf(stderr, "Error in bind: %s\n", strerror(errno));
            } else {
                fprintf(stderr, "Error in listen: %s\n", strerror(errno));
            }
            socket_close(self);
        }
    }
    return ERROR_CODE;
}

int socket_start(struct socket_t *self,
                struct addrinfo *info, bool is_server) {
    int status = 0;

    if (is_server) {
        status = socket_bind_listen(self, info);
    } else {
        status = socket_connect(self, info);
    }
    freeaddrinfo(info);
    return status;
}

int socket_send(struct socket_t *self, unsigned char *message, size_t msg_len) {
    size_t bytes_sent = 0;

    while (bytes_sent < msg_len) {
        size_t actually_sent = send(self->fd, &message[bytes_sent],
                            msg_len - bytes_sent, MSG_NOSIGNAL);

        if (actually_sent == 0) {
            return 0;
        } else if (actually_sent == -1) {
            fprintf(stderr, "Error in send :%s\n", strerror(errno));
            return ERROR_CODE;
        }
        bytes_sent += actually_sent;
    }
    return bytes_sent;
}

int socket_accept(struct socket_t *host, struct socket_t *client) {
    struct sockaddr_in address;
    socklen_t address_length = (socklen_t) sizeof(address);

    client->fd = accept(host->fd, (struct sockaddr *)&address, &address_length);
    if (client->fd == -1) {
        fprintf(stderr, "Error in accept: %s\n", strerror(errno));
        return ERROR_CODE;
    }
    return 0;
}

int socket_receive(struct socket_t *self,
                    unsigned char *buffer, size_t buffer_size) {
    size_t bytes_received = 0;

    while (bytes_received < buffer_size) {
        size_t actually_received = recv(self->fd, &buffer[bytes_received],
                                buffer_size - bytes_received, 0);
        if (actually_received == -1) {
            fprintf(stderr, "Error in receive: %s\n", strerror(errno));
            return ERROR_CODE;
        } else if (actually_received == 0) {
            return 0;
        }
        bytes_received += actually_received;
    }
    return bytes_received;
}

int socket_close(struct socket_t *self) {
    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);
    return 0;
}

int socket_destroy(struct socket_t *self) {
    self->fd = -1;
    return 0;
}
