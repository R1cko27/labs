#include <locale.h>
#include <stdio.h>

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Привет, мир!");
}
