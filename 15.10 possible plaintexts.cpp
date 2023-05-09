#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MSG_LEN 1000
#define NUM_LETTERS 26

char* decrypt(char* msg, int shift);
int get_shift(char* msg);
int cmp_freq(const void *a, const void *b);
void print_top_n(char** plaintexts, int* freqs, int n);

int main() {
    char msg[MAX_MSG_LEN];
    char* plaintexts[NUM_LETTERS];
    int freqs[NUM_LETTERS] = {0};

    printf("Enter the encrypted message: ");
    fgets(msg, MAX_MSG_LEN, stdin);

    int shift = get_shift(msg);
    printf("The shift is: %d\n", shift);

    for (int i = 0; i < NUM_LETTERS; i++) {
        plaintexts[i] = decrypt(msg, i);
        for (int j = 0; j < strlen(plaintexts[i]); j++) {
            char c = plaintexts[i][j];
            if (isalpha(c)) {
                freqs[c - 'a']++;
            }
        }
    }

    // Sort the plaintexts by frequency
    qsort(plaintexts, NUM_LETTERS, sizeof(char*), cmp_freq);

    int n;
    printf("How many plaintexts would you like to see? ");
    scanf("%d", &n);

    print_top_n(plaintexts, freqs, n);

    // Free dynamically allocated memory
    for (int i = 0; i < NUM_LETTERS; i++) {
        free(plaintexts[i]);
    }

    return 0;
}

char* decrypt(char* msg, int shift) {
    char* plaintext = (char*)malloc(strlen(msg) + 1);

    for (int i = 0; i < strlen(msg); i++) {
        char c = msg[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                plaintext[i] = 'A' + (c - 'A' + shift) % 26;
            } else {
                plaintext[i] = 'a' + (c - 'a' + shift) % 26;
            }
        } else {
            plaintext[i] = c;
        }
    }

    plaintext[strlen(msg)] = '\0';

    return plaintext;
}

int get_shift(char* msg) {
    int freqs[NUM_LETTERS] = {0};

    for (int i = 0; i < strlen(msg); i++) {
        char c = msg[i];
        if (isalpha(c)) {
            freqs[tolower(c) - 'a']++;
        }
    }

    // Find the most frequent letter in the encrypted message
    int max_freq = 0;
    int max_freq_idx = 0;
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (freqs[i] > max_freq) {
            max_freq = freqs[i];
            max_freq_idx = i;
        }
    }

    // Assume the most frequent letter in the encrypted message corresponds to 'e'
    int shift = (max_freq_idx + 22) % 26;

    return shift;
}

int cmp_freq(const void *a, const void *
