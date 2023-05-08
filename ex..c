#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void caesar_cipher(char *message, int key);

int main()
{
    char message[MAX_LEN];
    int key;

    printf("Enter a message to encrypt: ");
    fgets(message, MAX_LEN, stdin);

    printf("Enter a key value (1-25): ");
    scanf("%d", &key);

    caesar_cipher(message, key);

    printf("Encrypted message: %s\n", message);

    return 0;
}

void caesar_cipher(char *message, int key)
{
    int len = strlen(message),i;
    for ( i = 0; i < len; i++)
    {
        char ch = message[i];

        // If the character is an uppercase letter
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ((ch - 'A') + key) % 26 + 'A';
        }
        // If the character is a lowercase letter
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = ((ch - 'a') + key) % 26 + 'a';
        }
        message[i] = ch;
    }
}
