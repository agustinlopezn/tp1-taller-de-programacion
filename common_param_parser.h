#include <stdio.h>
#include <string.h>

// Parses the method from the arguments and returns the method
char *parser_get_method(char **method, char *argv_method, char *delim);

// Parses the key from the arguments and returns the key
char *parser_get_key(char **key, char *argv_key, char *delim);
