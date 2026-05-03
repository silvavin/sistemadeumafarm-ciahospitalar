#include <stdio.h>

int main() {
    int a, b, c;

    printf("Digite tres numeros inteiros: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a <= b && a <= c) {
    menor = a;
    if (b <= c) { meio = b; maior = c; } else { meio = c; maior = b; }
} else if (b <= a && b <= c) {
    menor = b;
    ...
} else {
    menor = c;

    return 0;
}


