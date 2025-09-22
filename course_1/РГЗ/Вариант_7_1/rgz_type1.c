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

int main(){
    int n,k;
    printf("Enter base: ");
    scanf("%d", &n);
    printf("Enter exponenta: ");
    scanf("%d", &k);
    long long number = degree(n,k);
    char answer[] = "%llx\n";
    printf(answer, number);
}