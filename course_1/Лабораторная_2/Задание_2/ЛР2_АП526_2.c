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

void func(int number) {
    int countOfNumber = 0;
    int i = 1;
    char answer[1000];
    answer[0] = '\0';

    while (countOfNumber < number) {
        int digits = Count_Pos(i);
        
        if (countOfNumber + digits > number) {
            int digitsNeeded = number - countOfNumber;
            int divisor = (int)pow(10, digits - digitsNeeded);
            int res = i / divisor;
            
            char str_res[2];
            sprintf(str_res, "%d", res);
            strcat(answer, str_res);
            break;
        }
        
        char str_i[20];
        sprintf(str_i, "%d", i);
        strcat(answer, str_i);
        countOfNumber += digits;
        i++;
    }
    printf("%s", answer);
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
    func(numberInput);
    return 0;
}