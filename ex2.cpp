#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void monoalphabetic_substitution(char *message, char *key);

int main()
{
    char message[MAX_LEN];
    char key[26];

    printf("Enter a message to encrypt: ");
    fgets(message, MAX_LEN, stdin);

    printf("Enter a substitution key (26 letters): ");
    fgets(key, 27, stdin);

    monoalphabetic_substitution(message, key);

    printf("Encrypted message: %s\n", message);

    return 0;
}

void monoalphabetic_substitution(char *message, char *key)
{
    int len = strlen(message);
    for (int i = 0; i < len; i++)
    {
        char ch = message[i];

        // If the character is an uppercase letter
        if (ch >= 'A' && ch <= 'Z')
        {
            message[i] = key[ch - 'A'];
        }
        // If the character is a lowercase letter
        else if (ch >= 'a' && ch <= 'z')
        {
            message[i] = key[ch - 'a'] + 'a' - 'A';
        }
    }
}
