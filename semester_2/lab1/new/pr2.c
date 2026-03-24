#include <stdio.h>

int reverse(int num, int reversed) {
    if (num < 10) {
        return reversed * 10 + num;
    }
    reversed = reversed * 10 + num % 10;
    num = num / 10;
    return reverse(num, reversed);
}

void answer(int number){
    if (number < 0) {
        printf("Изначальное число: %d. Перевернутое число: -%d\n", number, reverse(-number, 0));
    } else {
        printf("Изначальное число: %d. Перевернутое число: %d\n", number, reverse(number, 0));
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
