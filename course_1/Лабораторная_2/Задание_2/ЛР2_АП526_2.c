#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int Count_Pos(int number) {
    int p = 1;
    while ((number / (int)pow(10, p)) > 0) {
        p++;    
    }
    return p;
}

char* func(int number) {
    int countOfNumber = 0;
    int i = 1;
    char* answer = malloc(number + 1); // Динамическая память
    answer[0] = '\0'; // Делам ее изначально пустой

    while (countOfNumber < number) {
        int digits = Count_Pos(i);
        
        if (countOfNumber + digits > number) {
            int digitsNeeded = number - countOfNumber;
            int divisor = (int)pow(10, digits - digitsNeeded);
            int res = i / divisor;
            
            char str_res[2];
            sprintf(str_res, "%d", res); // Перевод числа в строку
            strcat(answer, str_res);
            break;
        }
        
        char str_i[20];
        sprintf(str_i, "%d", i); // Перевод числа в строку
        strcat(answer, str_i); // Конкатенция. К строке answer прибавляем str_i
        countOfNumber += digits;
        i++;
    }
    return answer;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int numberInput;

    printf("Введите любое число ");
    scanf("%d", &numberInput);
    
    while (numberInput <= 0) {
        printf("Ошибка, повторите еще раз\n");
        printf("Введите число ");
        scanf("%d", &numberInput);
    }
    
    char* answer = func(numberInput);
    printf("%s", answer);
    free(answer);  // Освобождаем память
    return 0;
}