#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAXLEN 150 // Максимальная длина строки
#define L 260 // Максимальная длина файла

char* Del_Str(char* str){
    if (str == NULL) return str;

    // Проверяем, есть ли в строке хотя бы одна цифра
    int has_digit = 0;
    char *temp = str;
    while (*temp != '\0') {
        if (*temp >= '0' && *temp <= '9') {
            has_digit = 1;
            break;
        }
        temp++;
    }
    
    // Если цифр нет - возвращаем пустую строку
    if (!has_digit) {
        str[0] = '\0';
        return str;
    }
    
    return str;
}

void answer(FILE *f1, FILE *f2) {
    char str[MAXLEN], *tmp;
    
    while(fgets(str, sizeof(str), f1) != NULL)
    {
        tmp = Del_Str(str);
        fputs(tmp, f2);
    }
    
    fclose(f1);
    fclose(f2);
    
    puts("The operation is complete. The result is written to the result1.txt file");
}

int main()
{
    FILE *f1, *f2;
    char fname[L], s[L];

    puts("\n Excluding a substring from the lines of a file.\n Enter the file name:");
    fgets(fname, sizeof(fname), stdin);
    fname[strcspn(fname, "\n")] = 0;
    
    if ((f1 = fopen(fname, "r")) == NULL)
    { 
        puts("Error when opening the source file!"); 
        return 1;
    }
    
    if ((f2 = fopen("result1.txt", "w")) == NULL)
    {
        puts("An error occurred while creating the result file!"); 
        fclose(f1);
        return 1;
    }
    
    answer(f1, f2);
    
    return 0;
}