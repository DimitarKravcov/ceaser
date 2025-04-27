#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000
char* cezar_cipher(char* str, int key)
{
    int lenght = strlen(str);
    char* cipher = (char*) malloc(sizeof(char) * (lenght + 1));
    for(int i = 0; i < lenght; i++)
    {
            if(str[i]>= 'a' && str[i] <= 'z'){
                cipher[i] = ((str[i] - 'a' + key) %26) + 'a';
            } else if (str[i] >= 'A' && str[i] <= 'Z'){
                cipher[i] = ((str[i] - 'A' + key) %26) + 'A';
            }else {
                cipher[i] = str[i];
            }
            
    }
    cipher[lenght] = '\0';
    return cipher;
}

int main()
{
    char str [MAXN];
    printf("Enter text: ");
    fgets(str, MAXN, stdin);
    str[strcspn(str, "\n")] = '\0';

    int key;
    printf("Enter key: ");
    scanf("%d", &key);
    char* cipher = cezar_cipher(str, key);
    printf("Text: %s\n", cipher);
    FILE* file = fopen("cipher_output.txt", "w");
    if(!file){
        perror("File failed");
        free(cipher);
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", cipher);
    fclose(file);
    free(cipher);
    return EXIT_SUCCESS;
}