#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLS 5

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[ROWS][COLS], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decode the Playfair code message
void decodePlayfair(char message[]) {
    char playfairMatrix[ROWS][COLS] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'E'},
        {'Z', 'W', 'E', 'H', 'E'},
        {'W', 'R', 'Y', 'T', 'U'},
        {'H', 'E', 'Y', 'F', 'S'}
    };

    int len = strlen(message);
    int i;

    for (i = 0; i < len; i += 2) {
        char ch1 = message[i];
        char ch2 = message[i + 1];

        if (ch1 == ' ') {
            printf(" ");
            i--;
            continue;
        }

        int row1, col1, row2, col2;
        findPosition(playfairMatrix, ch1, &row1, &col1);
        findPosition(playfairMatrix, ch2, &row2, &col2);

        char decodedCh1, decodedCh2;

        // Same row
        if (row1 == row2) {
            decodedCh1 = playfairMatrix[row1][(col1 + COLS - 1) % COLS];
            decodedCh2 = playfairMatrix[row2][(col2 + COLS - 1) % COLS];
        }
        // Same column
        else if (col1 == col2) {
            decodedCh1 = playfairMatrix[(row1 + ROWS - 1) % ROWS][col1];
            decodedCh2 = playfairMatrix[(row2 + ROWS - 1) % ROWS][col2];
        }
        // Different row and column
        else {
            decodedCh1 = playfairMatrix[row1][col2];
            decodedCh2 = playfairMatrix[row2][col1];
        }

        printf("%c%c", decodedCh1, decodedCh2);
    }

    printf("\n");
}

int main() {
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    decodePlayfair(message);

    return 0;
}
