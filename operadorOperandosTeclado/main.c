/**
* @file operador_y_operandos_teclado.c
* @brief programa incompleto que lee dos operandos y un operador aritmético,
*		 y muestra el resultado de la operación
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI, UPM
* @date 2023/02/07
* @last modified 2026/02/12
**/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>											// para imprimir por pantalla caracteres especiales en español
#include <float.h>											// max constants

#define MAX_BUFFER 30

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

typedef enum {
	NO_VALIDO = -1,
	SUMA = 0,
	RESTA,
	MUL,
	DIV
} operador_t;

/**
* @brief función que devuelve el operador_t correspondiente a un carácter,
*		 o -1 si el carácter no es un operador válido
**/
operador_t char_to_operador(char c)
{
	/* @todo ...  */
	return NO_VALIDO;
}

/**
* @brief función que devuelve el string con el operador aritmético correspondiente a un operador_t
**/
const char* operador_str(operador_t op)
{
	switch (op) {
	case SUMA:  return "+";
	case RESTA:	return "-";
	case MUL:	return "*";
	case DIV:	return "/";
	default:	return "?";
	}
}

/**
* @brief función que lee de stdin dos operandos y un operador aritmético, con validación de datos
* @param lhs puntero a float donde se guardará el primer operando
* @param rhs puntero a float donde se guardará el segundo operando
* @param op puntero a operador_t donde se guardará el operador aritmético
* @return void
* @details
*	- la función lee de stdin una línea, parsea los datos, valida que el operador sea correcto,
* 	  y guarda los resultados en las variables apuntadas por los parámetros. Si los datos no son correctos,
*	  se muestra un mensaje de error y se vuelve a pedir la entrada.
*	- se emplea un patrón seguro para leer del flujo de entrada: buffer con tamaño controlado + fgets
**/
void entrada_datos(float* lhs, float* rhs, operador_t* op)
{
	char buffer[MAX_BUFFER];
	char c;

	puts("Introduzca 2 números y un operador (+ - * /)");

	for (;;) {

		/* lee linea de stdin */
		read_status_t status = read_line(buffer, sizeof buffer);
		if (status != READ_OK) {
			puts("No se han podido leer los datos, vuelva a introducirlos");
			continue;
		}

		/* parseo seguro */
		if (sscanf(buffer, "%f %f %c", lhs, rhs, &c) != 3) {
			puts("Datos incorrectos, vuelva a introducirlos");
			continue;
		}

		/* lógica de parseo */
		operador_t op_tmp = char_to_operador(c);
		if (op_tmp == NO_VALIDO) {
			puts("Operador no válido");
			continue;
		}

		/* datos válidos - salida del bucle */
		*op = op_tmp;
		break;
	}
}

/**
 * @brief Realiza una operación aritmética básica entre dos operandos.
 *
 * Esta función ejecuta una operación matemática según el operador
 * especificado. Soporta suma, resta, multiplicación y división.
 *
 * @param lhs Operando izquierdo de la operación.
 * @param rhs Operando derecho de la operación.
 * @param op  Operador que indica la operación a realizar
 *            (SUMA, RESTA, MUL, DIV).
 *
 * @return Resultado de la operación como float.
 * @retval FLT_MAX Si ocurre un error:
 *         - División por cero.
 *         - Operador no válido.
 *
 * @note En caso de división por cero se muestra un mensaje
 *       de error por salida estándar.
 */
float operacion(float lhs, float rhs, operador_t op)
{
	/* @todo... */
	return FLT_MAX;
}

/******************
* Test Unitario
*******************/
int main() {
	float n1, n2;
	float resultado;
	operador_t op;

	//ver en consola caracteres especiales
	// (acentos, separador de miles...)
	setlocale(LC_ALL, "es-ES");

	entrada_datos(&n1, &n2, &op);
	printf("leidos: %f, %f, %s\n", n1, n2, operador_str(op));


	resultado = operacion(n1, n2, op);
	if (resultado != FLT_MAX) {											/* uso de la cte FTL_MAX como centinela */
		printf("Resultado: %.6f\n", resultado);
	}

	return 0;
}