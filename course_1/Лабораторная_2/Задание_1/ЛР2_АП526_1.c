#include <stdio.h>
#include <ctype.h>
#include <string.h>

void func(char *string){
    char new_string[1000] = "";
    char char_delet;
    int j = 0;
    string[strcspn(string, "\n")] = '\0';
    
    for (int i = 0; i < strlen(string); i++) {
        if (i == 0) {
            char_delet = string[i];
            printf("%c", string[i]);
            new_string[j++] = string[i];
        }
        
        if (char_delet == '0') {
            if (isalpha(string[i])) {
                char_delet = string[i];
                printf("%c", string[i]);
                new_string[j++] = string[i];
            }
        }
        
        if (string[i] == char_delet) {
            printf("");
        } else {
            printf("%c", string[i]);
            new_string[j++] = string[i];
        }
        
        if (!isalpha(string[i])) {
            char_delet = '0';
        }
    }
    
    new_string[j] = '\0';
    printf("\nРезультирующая строка: %s\n", new_string);
}
int main() {
    char string[1000];
    printf("Введите строку: ");
    fgets(string, sizeof(string), stdin);
    func(string);
    return 0;
}