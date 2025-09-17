#include <stdio.h>
#include <math.h>
#include <locale.h>

int Count_Pos(int number) {
    int p = 1;
    while ((number / (int)pow(10, p)) > 0) {
        p++;
    }
    return p;
}

void answer(int number) {
    int countOfNumber = 0;
    int i = 1;
    while (countOfNumber < number) {
        printf("%d", i);
        countOfNumber += Count_Pos(i);
        i++;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int numberInput;
    printf("Введите любое число ");
    scanf_s("%d", &numberInput);
    while (numberInput <= 0) {
        printf("Ошибка, повторите еще раз\n");
        printf("Введите число ");
        scanf_s("%d", &numberInput);
    }
    answer(numberInput);
    return 0;
}

