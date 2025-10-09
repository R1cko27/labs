#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

void func(char* string) {
    char char_delet;
    int j = 0;
    string[strcspn(string, "\n")] = '\0';
    printf("Ответ: ");
    for (int i = 0; i < strlen(string); i++) {
        if (i == 0) {
            char_delet = string[i];
            printf("%c", string[i]);
        }

        if (char_delet == '␦') {
            if (isalpha(string[i])) {
                char_delet = string[i];
                printf("%c", string[i]);
            }
        }

        if (string[i] == char_delet) {
            printf("");
        }

        else {
            printf("%c", string[i]);
        }

        if (!isalpha(string[i])) {
            char_delet = '␦';
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    char string[1000];
    printf("Введите строку: ");
    fgets(string, sizeof(string), stdin);
    func(string);
    return 0;
}