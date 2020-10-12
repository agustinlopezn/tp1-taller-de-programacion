#include <stdio.h>
#include <stdbool.h>

#define ANSI_COLOR_LGH_RED "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN "\x1b[1m\x1b[32m"

void print_test(char *message, bool ok) {
    printf("%s ", message);
    if (ok) {
        printf("%s", ANSI_COLOR_LGH_GREEN);
        printf("OK\n");
    } else {
        printf("%s", ANSI_COLOR_LGH_RED);
        printf("ERROR\n");
    }
    printf("\x1b[0m");  // resets the colour
}