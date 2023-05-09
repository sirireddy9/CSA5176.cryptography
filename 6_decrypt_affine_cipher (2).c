#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) {
        x1 += m0;
    }
    return x1;
}

int main() {
    char ciphertext[] = "UUYVBIUHHIICXJJSKUWLUYVBJJYKQQHIQJQJCZZXXJZJUYYVBIU";
    int freq[ALPHABET_SIZE] = {0};
    int i, j, k, a, b, max_freq, second_max_freq, max_index, second_max_index, decrypted_char;
    int num_chars = sizeof(ciphertext) / sizeof(ciphertext[0]);
    char decrypted_text[num_chars];
    for (i = 0; i < num_chars; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }
    max_freq = freq[1];
    max_index = 1;
    second_max_freq = freq[0];
    second_max_index = 0;
    for (i = 2; i < ALPHABET_SIZE; i++) {
        if (freq[i] > max_freq) {
            second_max_freq = max_freq;
            second_max_index = max_index;
            max_freq = freq[i];
            max_index = i;
        } else if (freq[i] > second_max_freq) {
            second_max_freq = freq[i];
            second_max_index = i;
        }
    }
    a = (max_index - second_max_index) % ALPHABET_SIZE;
    if (a < 0) {
        a += ALPHABET_SIZE;
    }
    b = (4 * (max_index - a)) % ALPHABET_SIZE;
    if (b < 0) {
        b += ALPHABET_SIZE;
    }
    printf("The affine cipher is: a=%d, b=%d\n", a, b);
    for (i = 0; i < num_chars; i++) {
        if (isalpha(ciphertext[i])) {
            decrypted_char = (mod_inverse(a, ALPHABET_SIZE) * ((toupper(ciphertext[i]) - 'A') - b)) % ALPHABET_SIZE;
            if (decrypted_char < 0) {
                decrypted_char += ALPHABET_SIZE;
            }
            decrypted_text[i] = decrypted_char + 'A';
        } else {
            decrypted_text[i] = ciphertext[i];
        }
    }
    printf("The decrypted text is: %s\n", decrypted_text);
    return 0;
}

