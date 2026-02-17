#include <stdio.h>
#include <stdlib.h>
#define TAM 3

int main(void) {

	int lista_pila[TAM] = { 0,1,2 };

	int* lista_heap = malloc(TAM * sizeof(*lista_heap));
	if (lista_heap == NULL) return 1;

	free(*lista_heap);
	lista_heap = NULL;

	return 0;
}




















