/**
* @file patron_lectura_linea_teclado.c
* @brief Ejemplo de lectura robusta de una línea de texto desde el teclado en C,
*		 manejando el caso de línea truncada.
* @details
*  - patrón: usa fgets + strchr para lectura de línea con un buffer de tamaño fijo.
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI, UPM
* @date 07/02/2026
* @last modified 13/02/2026
*/

#define MAX_TAM_LINEA 30		/* tamaño máximo de bytes a leer por linea de teclado */	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
read_status_t read_line(char* buffer, size_t size)
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

/***************
* TEST UNITARIO
****************/

int main(void) {

	char linea_por_teclado[MAX_TAM_LINEA];

	/* ver en consola caracteres especiales */
	/* (acentos orotgráficos) */
	setlocale(LC_ALL, "es-ES");

	puts("Introduzca una frase corta");

	read_status_t status = read_line(linea_por_teclado, sizeof linea_por_teclado);

	if (status == READ_ERROR) {			/* error muy raro desde flujo de teclado */
		perror("Error de lectura");
		return 1;						/* código de error */
	}

	if (status == READ_EOF) {
		puts("Fin de fichero detectado");	/* puede ocurrir desde teclado, p. ej. CTRL+Z en consola Windows*/
		return 0;
	}

	if (status == READ_TRUNCATED) {
		puts("Línea truncada");
		return 0;
	}

	/* linea leida correctamente, no excede el tamaño previsto */
	printf("Leído: %s", linea_por_teclado);

	return 0;
}

//Saltaban chiribitas de la fragua mientras Cibrán Cortiñas, solitario chispero de la 
//aldea de coruxeo, descansaba en su yacija de fuste. Fueron unas cinco o seis las 
//campanadas que 