#include "common_param_parser.h"

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