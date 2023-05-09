#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MATRIX_SIZE 5

void generate_keymatrix(char *key, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void encrypt(char *message, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void decrypt(char *message, char matrix[MATRIX_SIZE][MATRIX_SIZE]);

int main()
{
    char message[100];
    char key[26];

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newlines from message and key
    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    char matrix[MATRIX_SIZE][MATRIX_SIZE];

    generate_keymatrix(key, matrix);

    printf("Key matrix:\n");

    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) 
    {
        for (j = 0; j < MATRIX_SIZE; j++) 
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    encrypt(message, matrix);

    printf("Encrypted message: %s\n", message);

    decrypt(message, matrix);

    printf("Decrypted message: %s\n", message);

    return 0;
}

void generate_keymatrix(char *key, char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    int i, j, k;
    char *p = key;
    char letters[26] = "abcdefghiklmnopqrstuvwxyz";

    // Copy key into matrix, skipping repeated letters
    for (i = 0, k = 0; i < MATRIX_SIZE; i++) 
    {
        for (j = 0; j < MATRIX_SIZE; j++) 
        {
            if (*p != '\0') 
            {
                matrix[i][j] = toupper(*p);
                p++;
            }
            else 
            {
                // Fill remaining spaces in matrix with unused letters
                while (strchr(key, letters[k]) != NULL) 
                {
                    k++;
                }
                matrix[i][j] = toupper(letters[k]);
                k++;
            }
        }
    }
}

void encrypt(char *message, char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    int i, j;
    char ch1, ch2;
    int row1, col1, row2, col2;

    // Remove non-alpha characters from message
    for (i = 0; message[i] != '\0'; i++) 
    {
        if (!isalpha(message[i])) 
        {
            memmove(&message[i], &message[i + 1], strlen(message) - i);
        }
    }

    // Add padding character if message length is odd
    if (strlen(message) % 2 == 1) 
    {
        strcat(message, "X");
    }

    // Encrypt message two letters at a time
    for (i = 0; message[i] != '\0'; i += 2) 
    {
        ch1 = toupper(message[i]);
        ch2 = toupper(message[i + 1]);

        // Find positions of characters in matrix
        for (j = 0; j < MATRIX_SIZE; j++) 
        {
            if (strchr(matrix[j], ch1) != NULL) 
            {
                row1 = j;
                col1 = strchr(matrix[j], ch1) - matrix[j];
            }

            if (strchr

