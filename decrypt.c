#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *infile, *outfile;
    char ch;
    int key;

    infile = fopen("encrypted.txt", "r");
    if (infile == NULL) {
        printf("Грешка: Не може да се отвори encrypted.txt\n");
        return 1;
    }

    outfile = fopen("output.txt", "w");
    if (outfile == NULL) {
        printf("Грешка: Не може да се създаде output.txt\n");
        fclose(infile);
        return 1;
    }

    printf("Въведи ключ за декодиране: ");
    scanf("%d", &key);

    while ((ch = fgetc(infile)) != EOF) {
        if (isupper(ch)) {
            ch = (ch - 'A' - key + 26) % 26 + 'A';
        } else if (islower(ch)) {
            ch = (ch - 'a' - key + 26) % 26 + 'a';
        } else if (isdigit(ch)) {
            ch = (ch - '0' - key + 10) % 10 + '0';
        }

        fputc(ch, outfile);
    }

    printf("Декодиран текст записан в output.txt!\n");

    fclose(infile);
    fclose(outfile);
    return 0;
}
