/**
 * @file patron_lectura_linea_fichero.c
 * @brief Ejemplo de lectura segura de un archivo línea por línea
 *        con detección de truncamiento.
 *
 * @author Pablo San Segundo, curso Informática Industrial, ETSIDI, UPM
 * @date 2026-02-13
 *
 * @details
 * Este fichero contiene un ejemplo de programa que abre un archivo
 * de texto y lo procesa línea por línea utilizando una función
 * auxiliar robusta basada en fgets().
 *
 * La función read_line_from_file() encapsula la lógica de lectura
 * con control explícito de estados, distinguiendo entre:
 *
 *  - Lectura correcta de una línea completa (READ_OK)
 *  - Línea truncada por insuficiencia del buffer (READ_TRUNCATED)
 *  - Fin del flujo de entrada (READ_EOF)
 *  - Error de lectura (READ_ERROR)
 *
 * El diseño permite diferenciar claramente entre condiciones normales
 * (EOF) y situaciones excepcionales (errores o truncamientos), lo que
 * facilita la construcción de analizadores sintácticos robustos.
 *
 * @note
 * El programa ilustra un patrón de lectura seguro aplicable tanto
 * a archivos como a la entrada estándar (stdin).
 *
 * @warning
 * Si el tamaño del buffer es insuficiente para la entrada esperada,
 * se producirá un estado READ_TRUNCATED.
 *
 * @see read_line_from_file()
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "brock200_1.clq"
#define PATH "C:/Users/PABLO/Desktop/DimacsAndOthers/"

#define	MAX_TAM_LINEA 50		/* tamaño máximo de bytes a leer por linea de teclado */

typedef enum {
	READ_ERROR = 0,
	READ_EOF,
	READ_OK,
	READ_TRUNCATED
} read_status_t;

/**
 * @brief Lee una línea desde un flujo FILE* con control de truncamiento.
 *
 * @param buffer Puntero al buffer donde se almacenará la línea leída.
 * @param size   Tamaño del buffer en bytes, incluyendo el carácter nulo final.
 * @param fp     Flujo de entrada (por ejemplo, stdin o un archivo abierto).
 *
 * @return READ_OK        Si la lectura fue exitosa y la línea entró completa.
 * @return READ_TRUNCATED Si la línea excede el tamaño del buffer y fue truncada.
 * @return READ_EOF       Si se alcanza el final del flujo y no se leyó nada.
 * @return READ_ERROR     Si ocurre un error de lectura o parámetros inválidos.
 *
 * @details
 * Usa fgets(). Si no aparece '\n' en el buffer, puede ser truncamiento o
 * una última línea sin '\n'. Se distingue mirando el siguiente carácter:
 * - Si es EOF, la línea era completa (READ_OK).
 * - Si no es EOF, se descarta el resto de la línea hasta '\n' o EOF y se
 *   devuelve READ_TRUNCATED.
 *
 * No elimina el carácter '\n' del buffer si la lectura es exitosa.
 */
read_status_t read_line_from_file(char* buffer, size_t size, FILE* fp)
{
	int ch;
	if (buffer == NULL || size == 0 || fp == NULL)
		return READ_ERROR;

	if (fgets(buffer, (int)size, fp) == NULL) {
		/*if (ferror(fp))
			return READ_ERROR;*/
		if (feof(fp))
			return READ_EOF;

		return READ_ERROR;  /* si no es fin de fichero ERROR */
	}

	if (strchr(buffer, '\n') == NULL) {
		/* Puede ser truncamiento o última línea sin '\n' */
		ch = fgetc(fp);
		if (ch == EOF) {
			/* Última línea sin '\n', pero completa */
			return READ_OK;
		}

		/* No era EOF: es truncamiento. Devolver el carácter al flujo y limpiar. */
		ungetc(ch, fp);
		while ((ch = fgetc(fp)) != '\n' && ch != EOF)
			;

		return READ_TRUNCATED;
	}

	return READ_OK;
}

/********************
* TEST UNITARIO
********************/

int main(void) {
	char buffer[MAX_TAM_LINEA];
	read_status_t status;
	char filename[] = PATH FILE_NAME;

	FILE* fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Error al abrir el archivo %s\n", FILE_NAME);
		return EXIT_FAILURE;
	}

	/* leer el archivo línea por línea */
	/* A) usando el patrón con control de truncamiento */
	for (;;) {
		status = read_line_from_file(buffer, sizeof(buffer), fp);
		switch (status) {

		case READ_OK:
			printf("%s", buffer);
			/* parse(buffer); */
			break;

		case READ_TRUNCATED:
			fprintf(stderr, "Línea truncada: %s\n", buffer);
			/* decidir política: continuar o abortar */
			goto cleanup;

		case READ_EOF:
			goto cleanup;

		case READ_ERROR:
		default:
			fprintf(stderr, "Error de lectura\n");
			goto cleanup;
		}
	}

	/* B) patrón simple bucle while */
	/*while (fgets(buffer, sizeof(buffer), fp)) {
		printf("%s", buffer);
	}*/

cleanup:
	fclose(fp);
	return 0;
}