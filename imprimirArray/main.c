#include <stdio.h>
#include <stdlib.h>
#define N 1000

int main() {
	int* coleccion = (int*)malloc(N * sizeof(int));

	if (coleccion == NULL) {
		printf("Error: no hay memoria suficiente.\n");
		return 1;
	}

	for (int i = 0; i < N; i++) {
		coleccion[i] = i + 1;
	}

	for (int i = 0; i < N; i++) {
		printf("%d ", coleccion[i]);
	}

	printf("\n");

	free(coleccion);

	return 0;
}