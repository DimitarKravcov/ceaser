#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* vigenereEncrypt(char* plaintext, char* key)
{
    int length = strlen(plaintext);
    int keyLength = strlen(key);
    char* cipher = (char*) malloc(sizeof(char) * (length + 1));
    if (cipher == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    memset(cipher, '\0', sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int shift = tolower(key[i % keyLength]) - 'a';

            if (islower(plaintext[i]))
            {
                cipher[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            }
            else
            {
                cipher[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            }
        }
        else
        {
            cipher[i] = plaintext[i];
        }
    }
    cipher[length] = '\0';
    return cipher;
}

char* vigenereDecrypt(char* ciphertext, char* key)
{
    int length = strlen(ciphertext);
    int keyLength = strlen(key);
    char* plaintext = (char*) malloc(sizeof(char) * (length + 1));
    if (plaintext == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    memset(plaintext, '\0', sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            int shift = tolower(key[i % keyLength]) - 'a';

            if (islower(ciphertext[i]))
            {
                plaintext[i] = 'a' + (ciphertext[i] - 'a' - shift + 26) % 26;
            }
            else
            {
                plaintext[i] = 'A' + (ciphertext[i] - 'A' - shift + 26) % 26;
            }
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
    return plaintext;
}

int main()
{
    const int MAXN = 1024;
    char text[MAXN];
    char key[MAXN];
    int choice;

    printf("Меню:\n");
    printf("1 - Шифриране\n");
    printf("2 - Дешифриране\n");
    printf("Избери: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        FILE* inputFile = fopen("message.txt", "rt");
        if (inputFile == NULL) {
            printf("Грешка при отваряне на message.txt\n");
            return 1;
        }
        fgets(text, MAXN, inputFile);
        fclose(inputFile);

        printf("Въведи ключ за шифриране: ");
        scanf("%s", key);

        char* cipher = vigenereEncrypt(text, key);

        FILE* outputFile = fopen("encrypted.txt", "wt");
        if (outputFile == NULL) {
            printf("Грешка при създаване на encrypted.txt\n");
            free(cipher);
            return 1;
        }
        fprintf(outputFile, "%s", cipher);
        fclose(outputFile);

        printf("Текстът е шифриран в encrypted.txt\n");

        free(cipher);
    }
    else if (choice == 2)
    {
        FILE* inputFile = fopen("encrypted.txt", "rt");
        if (inputFile == NULL) {
            printf("Грешка при отваряне на encrypted.txt\n");
            return 1;
        }
        fgets(text, MAXN, inputFile);
        fclose(inputFile);

        FILE* keyFile = fopen("key.txt", "rt");
        if (keyFile == NULL) {
            printf("Грешка при отваряне на key.txt\n");
            return 1;
        }
        fscanf(keyFile, "%s", key);
        fclose(keyFile);

        char* plain = vigenereDecrypt(text, key);

        FILE* outputFile = fopen("decrypted.txt", "wt");
        if (outputFile == NULL) {
            printf("Грешка при създаване на decrypted.txt\n");
            free(plain);
            return 1;
        }
        fprintf(outputFile, "%s", plain);
        fclose(outputFile);

        printf("Текстът е декриптиран в decrypted.txt\n");

        free(plain);
    }
    else
    {
        printf("Невалиден избор.\n");
    }

    return EXIT_SUCCESS;
}
