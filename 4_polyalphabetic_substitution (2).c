#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int i, j, k, plaintext_len, key_len;
    plaintext_len = strlen(plaintext);
    key_len = strlen(key);
    for (i = 0, j = 0; i < plaintext_len; i++) {
        if (isalpha(plaintext[i])) {
            k = tolower(key[j]) - 'a';
            ciphertext[i] = ((tolower(plaintext[i]) - 'a' + k) % ALPHABET_SIZE) + 'a';
            j = (j + 1) % key_len;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[plaintext_len] = '\0';
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    int i, j, k, ciphertext_len, key_len;
    ciphertext_len = strlen(ciphertext);
    key_len = strlen(key);
    for (i = 0, j = 0; i < ciphertext_len; i++) {
        if (isalpha(ciphertext[i])) {
            k = tolower(key[j]) - 'a';
            plaintext[i] = (((tolower(ciphertext[i]) - 'a') - k + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
            j = (j + 1) % key_len;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[ciphertext_len] = '\0';
}

int main() {
    char plaintext[] = "Hello, world!";
    char key[] = "secret";
    char ciphertext[strlen(plaintext)];
    char decrypted_text[strlen(plaintext)];
    encrypt(plaintext, key, ciphertext);
    printf("The ciphertext is: %s\n", ciphertext);
    decrypt(ciphertext, key, decrypted_text);
    printf("The decrypted text is: %s\n", decrypted_text);
    return 0;
}

