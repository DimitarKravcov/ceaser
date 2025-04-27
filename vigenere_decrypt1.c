#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* vigenereDecrypt(char* cipher, char* key)
{
    int length = strlen(cipher);
    int keyLength = strlen(key);
    char* plaintext = (char*) malloc(sizeof(char) * (length + 1));
    memset(plaintext, '\0', sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++)
    {
        if (isalpha(cipher[i]))
        {
            int shift = tolower(key[i % keyLength]) - 'a';

            if (islower(cipher[i])) 
            {
                plaintext[i] = 'a' + (cipher[i] - 'a' - shift + 26) % 26;
            }
            else 
            {
                plaintext[i] = 'A' + (cipher[i] - 'A' - shift + 26) % 26;
            }
        }
        else
        {
            plaintext[i] = cipher[i];    
        }
    }
    plaintext[length] = '\0';
    return plaintext;
}

int main()
{
    const int MAXN = 1024;
    char cipher[MAXN];
    char key[MAXN];

    FILE* inputFile = fopen("encrypted.txt", "rt");
    if (inputFile == NULL) {
        printf("Грешка при отваряне на encrypted.txt\n");
        return 1;
    }
    fgets(cipher, MAXN, inputFile); 
    fclose(inputFile);

    FILE* keyFile = fopen("key.txt", "rt");
    if (keyFile == NULL) {
        printf("Грешка при отваряне на key.txt\n");
        return 1;
    }
    fscanf(keyFile, "%s", key); 
    fclose(keyFile);

    char* result = vigenereDecrypt(cipher, key);

    FILE* outputFile = fopen("decrypted.txt", "wt");
    if (outputFile == NULL) {
        printf("Грешка при създаване на decrypted.txt\n");
        free(result);
        return 1;
    }
    fprintf(outputFile, "%s", result);
    fclose(outputFile);

    printf("Декриптираният текст е записан в decrypted.txt\n");

    free(result);

    return EXIT_SUCCESS;
}
