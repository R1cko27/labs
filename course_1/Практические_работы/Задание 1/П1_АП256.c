#include <stdio.h>

void answer(int a, int b, int c){
    int new_c = c < a && c < b ? c : a < c && a < b ? a : b;
    int new_a = a > c && a > b ? a : c > a && c > b ? c : b;
    int new_b = a + b + c - new_c - new_a;
    printf("a = %d b = %d c = %d", new_a, new_b, new_c);
}
int main(){
    int a,b,c;
    scanf_s("%d", &a);
    scanf_s("%d", &b);
    scanf_s("%d", &c);
    answer(a, b, c);
    return 0;
}