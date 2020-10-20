#define _POSIX_C_SOURCE 201112L // Enables getaddrinfo

#include "common_connection_util.h"

#define ERROR_CODE -1

// change this function to another file
int common_get_address_info(const char *address, const char *port,
                            struct addrinfo **info, int flag) {
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flag;

    int error = getaddrinfo(address, port, &hints, info);

    if (error) {
        fprintf(stderr, "Error getting address info\n");
        return ERROR_CODE;
    }
    return 0;
}
