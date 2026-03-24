#include <stdio.h>

int reverseNumber(int num, int reversed) {
    if (num < 10) {
        return reversed * 10 + num;
    }
    return reverseNumber(num / 10, reversed * 10 + num % 10);
}


void answer(int number){
    if (number < 0) {
        printf("Изначальное число: %d. Перевернутое число: -%d\n", number, reverseNumber(-number, 0));
    } else {
        printf("Изначальное число: %d. Перевернутое число: %d\n", number, reverseNumber(number, 0));
    }
}
int main() {
    answer(5);
    answer(-9);
    answer(-23456);
    answer(8765424);
    answer(0);
    return 0;
}