#include <locale.h>
#include <stdio.h>

void type1(int number){
    int maxNumber;
    printf("Enter 1 number for type 1 ");
    scanf("%d", &maxNumber);
    for (int i = 2; i < number+1; i++){
        int temp_num;
        printf("Enter %d number for type 1 ", i);
        scanf("%d", &temp_num);
        if (temp_num > maxNumber){
            maxNumber = temp_num;
        }
    }
    printf("Max number in type 1 is %d\n", maxNumber);
}

void type2(int number){
    int maxNumber;
    int i = 1;
    printf("Enter 1 number for type 2 ");
    scanf("%d", &maxNumber);
    while (i < number){
        int temp_num;
        printf("Enter %d number for type 2 ", i+1);
        scanf("%d", &temp_num);
        i++;
        if (temp_num > maxNumber){
            maxNumber = temp_num;
        }
    }
    printf("Max number in type 2 is %d\n", maxNumber);
}

void type3(int number){
    int maxNumber;
    int i = 1;
    printf("Enter 1 number for type 3 ");
    scanf("%d", &maxNumber);
    do {
        int temp_num;
        printf("Enter %d number for type 3 ", i+1);
        scanf("%d", &temp_num);
        i++;
        if (temp_num > maxNumber){
            maxNumber = temp_num;
        }
    } while (i < number);
    printf("Max number in type 3 is %d\n", maxNumber);
}

int main(){
    int number;
    setlocale(LC_ALL, "Rus");
    printf("Enter count of numbers ");
    scanf("%d", &number);
    type1(number);
    type2(number);
    type3(number);
}