/**
* @file matriz_memoria_academico.c
* @brief Servicios para la asignación de memoria para una matriz N x M usando punteros a cada fila
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI, UPM
* @date 06/03/2022
* @last modified 12/02/2026
*/

#include <stdio.h>
#include <stdlib.h>

#define MAT_FORMAT "%f"					/* formato de impresión de la matriz, float o double */
typedef float mat_t;

/**
 * @brief liberción de memoria robusta para una matriz de N filas y
 *		  cualquier número de columnas
 * @param m matriz a liberar
 * @param N número de filas de la matriz
 */
void free_mat(mat_t** m, size_t N)
{
	size_t i;

	/* free(NULL) es seguro, pero m[i] no si m es null */
	if (m == NULL) return;

	for (i = 0; i < N; i++) {
		free(m[i]);
	}
	free(m);
}

/**
 * @brief reserva memoria robusta para una matriz de N filas x M columnas
 * @param N número de filas de la matriz
 * @param M número de columnas de la matriz
 * @return un puntero a la matriz reservada, o NULL si no se pudo reservar
 * @details
 *  - inicializa la matriz a cero (todas las celdas a 0)
 */

mat_t** allocate_mat(size_t N, size_t M)
{
	size_t i;

	if (N == 0 || M == 0)
		return NULL;

	mat_t** m = malloc(N * sizeof(*m));
	if (m == NULL)
		return NULL;

	for (i = 0; i < N; i++) {
		m[i] = calloc(M, sizeof(*m[i]));				/* inicializa todas las celdas a 0 */
		if (m[i] == NULL) {
			free_mat(m, i);								/* libera las filas ya reservadas */
			return NULL;
		}
	}

	return m;
}

/**
* @brief imprime una matriz en consola
* @param m matriz a imprimir
* @param N número de filas de la matriz
* @param M número de columnas de la matriz
**/
void print_mat(mat_t** m, size_t N, size_t M)
{
	size_t i, j;

	if (m == NULL || N == 0 || M == 0) {
		puts("matriz vacía");
		return;
	}

	for (i = 0; i < N; ++i) {
		if (m[i] == NULL) {
			puts("(fila NULL)");
			continue;
		}

		for (j = 0; j < M; ++j) {
			printf(MAT_FORMAT " ", m[i][j]);
		}
		putchar('\n');
	}
}

/******************
* TEST UNITARIO
*******************/

int main(void) {
	/* asignación dinámica de memoria para una matriz 2 x 3 */
	mat_t** mat = allocate_mat(2, 3);

	mat[0][0] = 1;
	mat[1][2] = 1;


	/* visualiza la matriz */
	print_mat(mat, 2, 3);

	/* libera la memoria */
	free_mat(mat, 2);			/* puntero mat queda "dangling" */
	mat = NULL;

	return 0;
}
