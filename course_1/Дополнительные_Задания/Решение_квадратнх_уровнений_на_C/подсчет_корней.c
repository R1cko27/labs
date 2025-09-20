#include <stdio.h>
#include <math.h>

void disc(int a, int b, int c) {
    int count = 0;
    double discr = b * b - 4 * a * c;
    
    if (discr < 0) count = 0;
    else if (discr == 0) count = 1; 
    else count = 2;
    
    if (count == 1) {
        double root1 = (-b+0.0) / (2 * a);
        printf("Answer %.2f\n", root1);
        printf("Number of roots %d", count);
    }
    else if (count == 2) {
        double root1 = (-b+0.0 + sqrt(discr)) / (2 * a);
        double root2 = (-b+0.0 - sqrt(discr)) / (2 * a);
        printf("Two roots: %.2f and %.2f. Number of roots: %d\n", root1, root2, count);
    }
    else {
        printf("Number of roots %d", count);
    }
}

int main() {
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    disc(a, b, c);
    return 0;
}