#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    char palabra[100];
    int i, j;
    char temp;

    printf("Introduce una palabra: ");
    if (scanf("%s", palabra) != 1) return 1;

    palabra[sizeof(palabra) - 1] = '\0'; // Asegurarse de que la cadena esté terminada en cero
    size_t n = strlen(palabra);

    for (i = 0, j = (int)n - 1; i < j; i++, j--) {
        temp = palabra[i];
        palabra[i] = palabra[j];
        palabra[j] = temp;
    }

    printf("Palabra invertida: %s\n", palabra);

    return 0;
}