#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int has_mod_inv(int a) {
    int i;
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int a;

    printf("Values of a that are not allowed:\n");
    for (a = 1; a < 26; a++) {
        if (gcd(a, 26) != 1 || !has_mod_inv(a)) {
            printf("%d ", a);
        }
    }
    printf("\n");

    return 0;
}
