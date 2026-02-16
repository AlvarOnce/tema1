/**
* @file ordenar_array.c
* @brief ordenamiento de los elementos de un array mediante un algoritmo de ordenamiento por selección simplificado:
*		 Fijada una posición i se compara contra todos los elementos a su derecha y se intercambia el valor de i
*		 por el valor del elemento que es menor (o mayor) que i. Al terminar, el elemento i-ésimo estará en su lugar.
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI UPM
* @date 12/02/2024
* @last modified 07/02/2026
**/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/****************
*Estructuras de datos
****************/

static int lista_num[] = { 1, 5, 4, 3, 2, 6 };


/****************
* Sercicios
****************/

static void orden_decreciente_por_seleccion_simplificado(int lista_num[], size_t n) {
	size_t i, j;
	int temp;

	for (i = 0; i + 1 < n; ++i) {
		for (j = i + 1; j < n; ++j) {

			if (lista_num[i] < lista_num[j]) {
				temp = lista_num[i];
				lista_num[i] = lista_num[j];
				lista_num[j] = temp;
			}

		}/* next j */
	}/* next i */
}

static void orden_creciente_por_seleccion_simplificado(int lista_num[], size_t n) {
	size_t i, j;
	int temp;

	for (i = 0; i + 1 < n; ++i) {
		for (j = i + 1; j < n; ++j) {

			if (lista_num[i] > lista_num[j]) {
				temp = lista_num[i];
				lista_num[i] = lista_num[j];
				lista_num[j] = temp;
			}

		}/* next j */
	}/* next i */
}

static void imprime_lista(const int v[], size_t n) {
	size_t i;

	printf("[");
	for (i = 0; i < n; ++i) {								/* espacios entre números menos al final */
		printf("%d%s", v[i], (i + 1 < n) ? " " : "");		/* ultima iteracion i + 1 = n */
	}
	puts("]");
}

/******************
* tests unitarios
*******************/

int main(void) {
	size_t n = sizeof(lista_num) / sizeof(lista_num[0]);

	orden_creciente_por_seleccion_simplificado(lista_num, n);
	imprime_lista(lista_num, n);

	orden_decreciente_por_seleccion_simplificado(lista_num, n);
	imprime_lista(lista_num, n);
	return 0;
}