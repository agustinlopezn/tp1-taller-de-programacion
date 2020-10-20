#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

struct addrinfo;

// Gets the address info, returns 0 in succes or -1 if an error occurred
int common_get_address_info(const char *address, const char *port,
                            struct addrinfo **info, int flag);

// Parses the method from the arguments and returns the method
char *parser_get_method(char **method, char *argv_method, char *delim);

// Parses the key from the arguments and returns the key
char *parser_get_key(char **key, char *argv_key, char *delim);
