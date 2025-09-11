#include <locale.h>
#include <stdio.h>

void type1(int number){
    int maxNumber;
    printf("Введите 1 число для типа 1 ");
    scanf_c("%d", &maxNumber);
    for (int i = 2; i < number+1; i++){
        int temp_num;
        printf("Введите %d число для типа 1 ", i);
        scanf_c("%d", &temp_num);
        if (temp_num > maxNumber){
            maxNumber = temp_num;
        }
    }
    printf("Max number in type 1 is %d\n", maxNumber);
}

void type2(int number){
    int maxNumber;
    int i = 1;
    printf("Введите 1 число для типа 2 ");
    scanf_c("%d", &maxNumber);
    while (i < number){
        int temp_num;
        printf("Введите %d число для типа 2 ", i+1);
        scanf_c("%d", &temp_num);
        i++;
        if (temp_num > maxNumber){
            maxNumber = temp_num;
        }
    }
    printf("Максимальное число в типе 2: %d\n", maxNumber);
}

void type3(int number){
    int maxNumber;
    int i = 1;
    printf("Введите 1 число для типа 3 ");
    scanf_c("%d", &maxNumber);
    do {
        int temp_num;
        printf("Введите %d число для типа 3 ", i+1);
        scanf_c("%d", &temp_num);
        i++;
        if (temp_num > maxNumber){
            maxNumber = temp_num;
        }
    } while (i < number);
    printf("Максимальное число в типе 3: %d\n", maxNumber);
}

int main(){
    int number;
    int chose;
    setlocale(LC_ALL, "Rus");
    printf("Введите количество чисел ");
    scanf_c("%d", &number);
    printf("Выбирите функцию, которую хотите использовать\n1. Цикл for (type1)\n2. Цикл while (type2)\n3. Цикл do (type3)\n");
    scanf_c("%d", &chose);
    if (chose == 1){
        type1(number);
    } else if (chose == 2){
        type2(number);
    } else if (chose == 3){
        type3(number);
    } else {
        printf("Неизвестный выбор");
    }
}