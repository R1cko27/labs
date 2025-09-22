#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long degree(int base, int exp){
    if (exp == 0){
        return 1;
    }
    long long result = 1;
    for(int i = 0; i < exp; i++){
        result *= base;
    }
    return result;
}

char* hex(long long number){
    char alph[16] = "0123456789ABCDEF";
    static char str[32] = "";
    str[0] = '\0';
    long long temp = number;
    int digits = 0;
    while (temp > 0){
        digits++;
        temp /= 16;
    }
    str[digits] = '\0';
    temp = number;
    for (int i = digits - 1; i >= 0; i--){
        str[i] = alph[temp%16];
        temp /= 16;
    }
    return str;
}

int main(){
    int n,k;
    printf("Enter base: ");
    scanf("%d", &n);
    printf("Enter exponenta: ");
    scanf("%d", &k);
    long long number = degree(n,k);
    char* answer = hex(number);
    printf("Answer: %s\n", answer);
}