/**
* @file matriz_memoria_pro.c
* @brief Servicios para la asignación de memoria para una matriz N x M usando un único bloque de memoria contigua
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI, UPM
* @date 06/03/2022
* @last modified 12/02/2026
*/

#include <stdio.h>
#include <stdlib.h>

#define MAT_FORMAT "%f"					/* formato de impresión de la matriz, float o double */
typedef float mat_t;

/**
 * @brief Libera la memoria de una matriz bidimensional
 *        reservada previamente con allocate_mat, siempre que
 *        haya sido asignada en un único bloque contiguo.
 *
 * @param m Matriz a liberar.
 *
 * @note Esta función asume que la matriz fue reservada con dos
 *       llamadas a malloc: una para el array de punteros y otra
 *       para el bloque contiguo de datos.
 */
void free_mat(mat_t** m)  // Hay que pasar m por referencia con *** para ponerle NULL al puntero y no a la copia del puntero (puntero colgante)
{
	free(m[0]);		/* libera el bloque contiguo de celdas */
	free(m);		/* libera el array de punteros */
}

/**
 * @brief Reserva e inicializa una matriz bidimensional contigua de N x M elementos.
 *
 * @param N Número de filas (debe ser > 0).
 * @param M Número de columnas (debe ser > 0).
 *
 * @return
 *  - Puntero a un array de N punteros, cada uno representando una fila.
 *  - NULL si ocurre algún error (N == 0, M == 0 o fallo de memoria).
 *
 * @details
 *  Diseño de memoria:
 *  -------------------
 *  La matriz se implementa en dos bloques dinámicos:
 *
 *   1) Un bloque contiguo de N*M elementos (datos reales).
 *   2) Un array de N punteros que referencian el inicio de cada fila.
 *
 *  Esto permite:
 *    - Acceso natural con notación mat[i][j].
 *    - Excelente localidad de memoria (cache-friendly).
 *    - Un único bloque contiguo para los datos.
 *
 *  Inicialización:
 *  ---------------
 *  Todos los elementos se inicializan a 0 mediante calloc().
 *
 *  Liberación:
 *  -----------
 *  Dado que existen dos bloques dinámicos, la liberación debe hacerse así:
 *
 *      free(mat[0]);   // libera el bloque contiguo de datos
 *      free(mat);      // libera el array de punteros a filas
 *
 *  Complejidad:
 *  ------------
 *    - Tiempo: O(N) para inicializar los punteros a filas.
 *    - Espacio: O(N*M) para los datos + O(N) para los punteros.
 *
 *  Seguridad:
 *  ----------
 *  - Si la reserva del segundo bloque falla, el primero se libera
 *    antes de retornar NULL (evita fugas de memoria).
 *  - No se realiza verificación de overflow en la multiplicación N*M.
 *    Si N y M pueden ser grandes, debería añadirse.
 *
 *  Limitaciones:
 *  -------------
 *  - No soporta redimensionamiento.
 *  - Requiere que el usuario conozca el protocolo de liberación.
 */
mat_t** allocate_mat(size_t N, size_t M)
{
	size_t i;

	if (N == 0 || M == 0)
		return NULL;

	mat_t* table = calloc(N * M, sizeof(*table));

	if (table == NULL)
		return NULL;

	mat_t** ptrs = malloc(N * sizeof(*ptrs));
	if (ptrs == NULL) {
		free(table);              /* liberar antes de salir */
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		ptrs[i] = table + i * M;
	}

	return ptrs;
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
	mat[0][1] = 1;

	/* visualiza la matriz */
	print_mat(mat, 2, 3);

	/* libera la memoria */
	free_mat(mat);				/* puntero mat queda "dangling" */
	mat = NULL;					/* se asigna NULL */
}
