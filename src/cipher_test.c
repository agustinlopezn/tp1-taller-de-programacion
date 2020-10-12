#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cipher.h"

#define ANSI_COLOR_LGH_RED	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"

void print_test(char *message, bool ok) {
    printf("%s ", message);
    if (ok) {
        printf(ANSI_COLOR_LGH_GREEN);
        printf("OK\n");
    } else {
        printf(ANSI_COLOR_LGH_RED);
        printf("ERROR\n");
    }
    printf("\x1b[0m"); //resets the colour
}

// Caesar tests
void large_n_caesar_test() {
    int n = 256;
    char input[5];
    char expected_output[5];
    strncpy(input, "hola", 5);
    strncpy(expected_output, "hola", 5);
    bool ok = false;

    char *output = cipher_caesar(input, n);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }
    
    print_test("Large n:", ok);
}

void small_n_caesar_test() {
    int n = 3;
    char input[5];
    char expected_output[5];
    strncpy(input, "hola", 5);
    strncpy(expected_output, "krod", 5);
    bool ok = false;

    char *output = cipher_caesar(input, n);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }

    print_test("Small n:", ok);
}

void zero_n_caesar_test() {
    int n = 0;
    char input[5];
    char expected_output[5];
    strncpy(input, "hola", 5);
    strncpy(expected_output, "hola", 5);
    bool ok = false;

    char *output = cipher_caesar(input, n);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }

    print_test("Zero n:", ok);
}

void null_string_caesar_test() {

}

// Vignere tests

void null_string_vignere_test() {
    
}

void same_len_input_and_key_vignere_test() {
    char input[5];
    char secret_key[5];
    char expected_output[5];
    strncpy(input, "0123", 5);
    strncpy(secret_key, "&$#!", 5);
    strncpy(expected_output, "VUUT", 5);
    bool ok = false;

    char *output = cipher_vignere(input, secret_key);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }

    print_test("Same length input and secret key:", ok);
}
void smaller_key_vignere_test() {
    char input[5];
    char secret_key[3];
    char expected_output[5];
    strncpy(input, "0123", 5);
    strncpy(secret_key, "&$", 3);
    strncpy(expected_output, "VUXW", 5);
    bool ok = false;

    char *output = cipher_vignere(input, secret_key);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }

    print_test("Smaller key than input:", ok);
}

void larger_key_vignere_test() {
    char input[5];
    char secret_key[10];
    char expected_output[5];
    strncpy(input, "0123", 5);
    strncpy(secret_key, "&$#!akjas", 10);
    strncpy(expected_output, "VUUT", 5);
    bool ok = false;

    char *output = cipher_vignere(input, secret_key);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }

    print_test("Larger key than input:", ok);
}

void large_input_vignere_test() {
    char input[20];
    char secret_key[10];
    char expected_output[20];
    strncpy(input, "0123012301230123012", 20);
    strncpy(secret_key, "&$#!", 5);
    strncpy(expected_output, "VUUTVUUTVUUTVUUTVUU", 20);
    bool ok = false;

    char *output = cipher_vignere(input, secret_key);

    if (strcmp(output, expected_output) == 0) {
        ok = true;
    }

    print_test("Larger key than input:", ok);
}

// RC4 tests

void null_string_rc4_test() {
    
}

void rc4_test() {
    char input[6];
    char secret_key[5];
    strncpy(input, "pedia", 6);
    strncpy(secret_key, "Wiki", 5);
    
    char *output = cipher_rc4(input, secret_key);
    for(int i = 0; i < strlen(output); i++){
        printf("%02x", output[i]);
    }
}

int main() {
    //Caesar tests
    printf("CIPHER TESTS\n\n");
    small_n_caesar_test();
    large_n_caesar_test();
    zero_n_caesar_test();

    //Vignere tests
    printf("\n\nVIGNERE TESTS\n\n");
    same_len_input_and_key_vignere_test();
    smaller_key_vignere_test();
    larger_key_vignere_test();
    large_input_vignere_test();

    //RC4 tests
    printf("RC4 TESTS\n\n");
    rc4_test();
    return 0;
}