/**
* @file centroide_teclado_inco.c
* @brief Programa incompleto en C que calcula el centroide de una nube de puntos 2D y lee los puntos desde teclado
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI, UPM
* @date 03/02/2025
* @last modified 12/02/2026
**/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>				/* para strchr */

#define MAX_PUNTOS_EN_NUBE 3
#define MAX_BUFFER_LINEA 100

typedef struct {
	double x;
	double y;
} punto_t;


typedef enum {
	READ_ERROR = 0,
	READ_EOF,
	READ_OK,
	READ_TRUNCATED
} read_status_t;

/**
 * @brief Lee una línea desde el flujo estándar de entrada (stdin)
 *		  con control de truncamiento.
 *
 * @param buffer Puntero al buffer donde se almacenará la línea leída.
 * @param size Tamaño del buffer en bytes, incluyendo el carácter nulo final.
 *
 * @return READ_OK        Si la lectura fue exitosa y la línea entró completa.
 * @return READ_TRUNCATED Si la línea excede el tamaño del buffer y fue truncada.
 * @return READ_ERROR     Si ocurre un error de lectura o parámetros inválidos.
 * @return READ_EOF      Si se alcanza el final del flujo estándar de entrada
 *                        (por ejemplo, tras una señal de fin de fichero en
 *                        modo consola).
 *
 * @details
 * La función utiliza fgets() para leer una línea desde la entrada estándar.
 * Si la línea leída no contiene el carácter '\n', se asume que fue truncada.
 * En ese caso, se descartan los caracteres restantes en stdin hasta encontrar
 * un salto de línea o EOF, evitando que afecten lecturas posteriores.
 *
 * No elimina el carácter '\n' del buffer si la lectura es exitosa.
 *
 * @note Es responsabilidad del llamador asegurarse de que el buffer tenga
 *       suficiente espacio para la entrada esperada.
 */
static read_status_t read_line(char* buffer, size_t size)
{
	int ch;
	if (buffer == NULL || size == 0)
		return READ_ERROR;

	if (fgets(buffer, (int)size, stdin) == NULL) {
		if (ferror(stdin))
			return READ_ERROR;
		if (feof(stdin))
			return READ_EOF;

		return READ_ERROR;  /* fallback defensivo */
	}

	if (strchr(buffer, '\n') == NULL) {

		/* la línea fue truncada, limpiar el resto de stdin */
		while ((ch = getchar()) != '\n' && ch != EOF)
			;

		return READ_TRUNCATED;
	}

	return READ_OK;
}

void imprime_punto(punto_t p) {
	printf("(%.2f, %.2f)\n", p.x, p.y);		/* punto_t coordendas float o double */
}

void imprime_nube_de_puntos(const punto_t nube_puntos[], size_t nPuntos) {
	if (nube_puntos == NULL || nPuntos == 0) {
		puts("Nube de puntos vacia o invalida.");	/* casos que se pueden separar */
		return;
	}
	for (size_t i = 0; i < nPuntos; i++) {
		imprime_punto(nube_puntos[i]);
	}
}

/**
* @brief Calcula el centroide de un array de puntos.
* @param lp Array de puntos
* @param nPuntos Número de puntos en el array
* @return El centroide de los puntos como un punto_t
* @details
*  - Si el array es NULL o el número de puntos es menor o igual a 0,
*    se devuelve un punto con coordenadas (0.0, 0.0).
*/
punto_t calcula_centroide(const punto_t nube_puntos[], size_t nPuntos)
{
	punto_t pres = { 0.0, 0.0 };
	double sumx = 0.0;
	double sumy = 0.0;
	size_t i;

	if (nube_puntos == NULL || nPuntos == 0) {
		return pres;
	}

	for (i = 0; i < nPuntos; i++) {
		sumx += nube_puntos[i].x;
		sumy += nube_puntos[i].y;
	}

	pres.x = sumx / nPuntos;
	pres.y = sumy / nPuntos;
	return pres;
}

/**
* @brief Lee una nube de puntos desde teclado.
* @param nube_puntos Puntero a un array de punto_t donde se almacenarán los puntos leídos
* @param nPuntos Número de puntos a leer
* @return 0 si la lectura fue exitosa, o un código de error (1) en caso contrario
**/
int leer_nube_de_puntos_desde_teclado(punto_t* nube_puntos, size_t nPuntos)
{
	char buffer[MAX_BUFFER_LINEA] = "";
	size_t i;
	read_status_t status = READ_OK;

	if (nube_puntos == NULL || nPuntos == 0) {
		return 1;
	}

	for (i = 0; i < nPuntos; i++) {

		for (;;) {

			printf("Introduzca las coordenadas (x y) para el punto %zu:	", i + 1);

			status = read_line(buffer, sizeof(buffer));

			if (status == READ_ERROR || status == READ_EOF) {
				puts("Error crítico o fin de flujo durante la lectura.");
				return 1;
			}

			if (status == READ_TRUNCATED) {
				puts("La línea introducida es demasiado larga. Inténtelo de nuevo.");
				continue;
			}

			if (sscanf(buffer, "%lf %lf", &nube_puntos[i].x, &nube_puntos[i].y) == 2) {
				break;
			}
			else {
				puts("Formato incorrecto. Introduzca dos números separados por un espacio.");
			}

		} /* nueva entrada mismo punto por error */

	} /* siguiente punto */

	return 0;
}

/**
* @brief Crea una nube de puntos leyendo desde teclado.
* @param nPuntos Número de puntos a leer
* @return Puntero a un array de punto_t con los puntos leídos, o NULL en caso de error
**/
punto_t* make_nube_de_puntos_desde_teclado(size_t nPuntos)
{
	punto_t* nube_puntos = malloc(nPuntos * sizeof(punto_t));
	
	if (nPuntos == NULL) return NULL;

	if (leer_nube_de_puntos_desde_teclado(nube_puntos, nPuntos) != 0) {
		free(nube_puntos);
		return NULL;
	}

	return nube_puntos;
}

/****************************
*
* TESTS UNITARIOS
*
*****************************/

int main(void) {
	punto_t centroide;

	punto_t* nube_puntos = make_nube_de_puntos_desde_teclado(MAX_PUNTOS_EN_NUBE);
	if (nube_puntos == NULL) {
		puts("Error al leer la nube de puntos.");
		return EXIT_FAILURE;
	}

	/* Mostrar puntos */
	imprime_nube_de_puntos(nube_puntos, MAX_PUNTOS_EN_NUBE);

	puts("************");

	/* Calcular y mostrar centroide */
	centroide = calcula_centroide(nube_puntos, MAX_PUNTOS_EN_NUBE);
	imprime_punto(centroide);

	free(nube_puntos);
	return EXIT_SUCCESS;
}

