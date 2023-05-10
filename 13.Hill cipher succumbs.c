#include <stdio.h>

#define MATRIX_SIZE 2

// Function to calculate the determinant of a 2x2 matrix
int calculateDeterminant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to calculate the modular inverse of a number
int calculateModularInverse(int num, int modulo) {
    int inverse;
    num = num % modulo;

    for (inverse = 1; inverse < modulo; inverse++) {
        if ((num * inverse) % modulo == 1) {
            return inverse;
        }
    }

    return -1; // Modular inverse doesn't exist
}

// Function to perform matrix multiplication
void matrixMultiplication(int matrix[MATRIX_SIZE][MATRIX_SIZE], int vector[MATRIX_SIZE]) {
    int result[MATRIX_SIZE];
    int i, j;

    for (i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;

        for (j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    for (i = 0; i < MATRIX_SIZE; i++) {
        vector[i] = result[i];
    }
}

// Function to encrypt a message using the Hill cipher
void encryptMessage(int matrix[MATRIX_SIZE][MATRIX_SIZE], int message[MATRIX_SIZE]) {
    matrixMultiplication(matrix, message);
}

// Function to decrypt a message using the Hill cipher
void decryptMessage(int matrix[MATRIX_SIZE][MATRIX_SIZE], int message[MATRIX_SIZE]) {
    int determinant = calculateDeterminant(matrix);
    int modulo = 26; // Hill cipher uses modulo 26

    int modularInverse = calculateModularInverse(determinant, modulo);
    if (modularInverse == -1) {
        printf("Modular inverse doesn't exist.\n");
        return;
    }

    int adjugate[MATRIX_SIZE][MATRIX_SIZE];
    adjugate[0][0] = matrix[1][1];
    adjugate[0][1] = -matrix[0][1];
    adjugate[1][0] = -matrix[1][0];
    adjugate[1][1] = matrix[0][0];

    int inverseMatrix[MATRIX_SIZE][MATRIX_SIZE];

    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            inverseMatrix[i][j] = (adjugate[i][j] * modularInverse) % modulo;

            // Ensure positive values for inverse matrix elements
            if (inverseMatrix[i][j] < 0) {
                inverseMatrix[i][j] += modulo;
            }
        }
    }

    matrixMultiplication(inverseMatrix, message);
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {3, 2},
        {5, 7}
    };

    int plaintext[MATRIX_SIZE] = {10, 7};
    int ciphertext[MATRIX_SIZE];

    encryptMessage(key, plaintext);

    printf("Encrypted message: ");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%d ", plaintext[i]);






