#include <stdio.h>
#define TAM 4


typedef struct {
    float x;
    float y;
} Punto;

Punto calcular_centroide(Punto lista_puntos[], int cantidad) {
    Punto centroide = { 0.0, 0.0 };

    for (int i = 0; i < cantidad; i++) {
        centroide.x += lista_puntos[i].x;
        centroide.y += lista_puntos[i].y;
    }

    if (cantidad > 0) {
        centroide.x /= cantidad;
        centroide.y /= cantidad;
    }

    return centroide;
}

void imprime_punto(Punto p) {
    printf("(%.2f, %.2f)\n", p.x, p.y);
}

void imprime_nube_de_puntos(const Punto nube_de_puntos[], int cantidad) {
    int i = 0;
    for (i = 0; i < cantidad; i++) {
        imprime_punto(nube_de_puntos[i]);
    }
}

int main() {
    Punto nube_de_puntos[TAM] = {
        {10.0, 2.0},
        {3.0, 4.0},
        {5.0, 3.0},
        {25.5, 6.0}

    };

    imprime_nube_de_puntos(nube_de_puntos, TAM);

    Punto resultado = calcular_centroide(nube_de_puntos, TAM);

    printf("El centroide es: (%.2f, %.2f)\n", resultado.x, resultado.y);

    return 0;
}