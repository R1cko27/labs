#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

void func(char* string) {
    int char_delet;
    int j = 0;
    string[strcspn(string, "\n")] = '\0';
    printf("Ответ: ");
    
    // Используем int вместо char для хранения символа удаления
    // Инициализируем специальным значением -1 (невалидный символ)
    char_delet = -1;
    
    for (int i = 0; i < strlen(string); i++) {
        // Если это первый символ или у нас не установлен символ для удаления
        if (char_delet == -1) {
            if (isalpha((unsigned char)string[i])) {
                char_delet = (unsigned char)string[i];
                printf("%c", string[i]);
            } else {
                // Если первый символ не буква, просто выводим его
                printf("%c", string[i]);
            }
            continue;
        }

        // Если текущий символ совпадает с символом для удаления
        if ((unsigned char)string[i] == char_delet) {
            continue; // пропускаем его
        }
        
        // Если встречаем не-букву, сбрасываем символ для удаления
        if (!isalpha((unsigned char)string[i])) {
            char_delet = -1;
        }
        
        printf("%c", string[i]);
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