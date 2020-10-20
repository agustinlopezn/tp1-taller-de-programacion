#define _POSIX_C_SOURCE 201112L // Enables getaddrinfo
#include "common.h"

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

char *parser_get_method(char **method, char *argv_method, char *delim) {
    strtok(argv_method, delim);
    *method = strtok(NULL, delim);

    if (!*method) {
        fprintf(stderr, "Error getting method\n");
    }

    return *method;
}

char *parser_get_key(char **key, char *argv_key, char *delim) {
    strtok(argv_key, delim);
    *key = strtok(NULL, delim);

    if (!*key) {
        fprintf(stderr, "Error getting key\n");
    }

    return *key;
}