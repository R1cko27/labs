#include <locale.h>
#include <stdio.h>

void type1(int number) {
    long long maxNumber;
    for (int i = 0; i < number; i++) {
        long long temp_num;
        printf("Введите %d число для типа 1 ", i + 1);
        scanf_s("%lld", &temp_num);
        if (i == 0) {
            maxNumber = temp_num;
        }
        else {
            if (temp_num > maxNumber) {
                maxNumber = temp_num;
            }
        }
    }
    printf("Максимальное число в типе 1: %lld\n", maxNumber);
}

void type2(int number) {
    long long maxNumber;
    int i = 0;
    while (i < number) {
        long long temp_num;
        printf("Введите %d число для типа 2 ", i + 1);
        scanf_s("%lld", &temp_num);
        if (i == 0) {
            maxNumber = temp_num;
        }
        else {
            if (temp_num > maxNumber) {
                maxNumber = temp_num;
            }
        }
        i++;
    }
    printf("Максимальное число в типе 2: %lld\n", maxNumber);
}

void type3(int number) {
    long long maxNumber;
    int i = 0;
    do {
        long long temp_num;
        printf("Введите %d число для типа 3 ", i + 1);
        scanf_s("%lld", &temp_num);
        if (i == 0) {
            maxNumber = temp_num;
        }
        else {
            if (temp_num > maxNumber) {
                maxNumber = temp_num;
            }
        }
        i++;
    } while (i < number);
    printf("Максимальное число в типе 3: %lld\n", maxNumber);
}

int main() {
    int number;
    int chose;
    setlocale(LC_ALL, "Rus");
    printf("Введите количество чисел ");
    scanf_s("%d", &number);
    printf("Выбирите функцию, которую хотите использовать\n1. Цикл for (type 1)\n2. Цикл while (type 2)\n3. Цикл do (type 3)\n");
    scanf_s("%d", &chose);
    if (chose == 1) {
        type1(number);
    }
    else if (chose == 2) {
        type2(number);
    }
    else if (chose == 3) {
        type3(number);
    }
    else {
        printf("Неизвестный выбор");
    }
}
