/**
* @file operador_y_operandos_inco.c
* @brief programa incompleto que lee dos operandos y un operador aritmético,
*		 y muestra el resultado de la operación (no compila)
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI UPM
* @date 2023/02/07
* @last modified 2026/02/06
**/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>							/* para formato decimal con coma en España */
#include <float.h>							/* centinela FLT_MAX para indicar error en la operación */

#define MAX_BUFFER 1000

typedef enum {
	SUMA = 0,
	RESTA,
	MUL,
	DIV,
	NINGUNO = -1
} operador_t;

/**
* @brief función que devuelve el string con el operador aritmético correspondiente a un operador_t
**/
const char* operador_str(operador_t op)
{
	switch (op) {
	case SUMA:	return "+";
	case RESTA:	return "-";
	case MUL:	return "*";
	case DIV:	return "/";
	case NINGUNO:	return "NINGUNO";
	}
}

/**
* @brief función que realiza la operación aritmética indicada por el operador_t sobre los operandos
* @param lhs el operando izquierdo (left-hand side)
* @param rhs el operando derecho (right-hand side)
* @param op el operador aritmético a aplicar
* @return el resultado de la operación, o FLT_MAX si el operador no es válido o si se intenta dividir por cero
*
* todo: patrón mejor para controlar el error - devolver un bool y el resultado por referencia
* todo: usar NAN incluido en math.h en lugar de FLT_MAX para indicar error en la operación
**/
long long resuelve_operacion(long long lhs, long long rhs, operador_t operacion)
{
	switch (operacion) {
	case SUMA:
		return lhs + rhs;
	case RESTA:
		return lhs - rhs;
	case MUL:
		return lhs * rhs;
	case DIV:
		if (rhs == 0) return (long long)FLT_MAX;
		return lhs / rhs;
	default:
		return (long long)FLT_MAX;
	}
	 
}

operador_t char_a_operador(char c) {
	switch (c) {
	case '+': return SUMA;
	case '-': return RESTA;
	case '*': return MUL;
	case '/': return DIV;
	default:  return NINGUNO;
	}
}

/******************
* tests unitarios
*******************/

int main(void) {
	long long operando_izq = 0;
	long long operando_der = 0;
	char simbolo;
	operador_t operacion = NINGUNO;

	/* ver en consola caracteres especiales
	  (aquí, coma para separador de miles y decimales en España) */
	setlocale(LC_ALL, "es_ES");

	printf("Introduzca operando izquierdo:\n");
	while (scanf_s("%lld", &operando_izq) != 1) {
		printf("Debe introducir un número:\n");
		while (getchar() != '\n');
	}

	printf("Introduzca operador (+, -, *, /):\n");
	scanf_s(" %c", &simbolo, 1);

	while (simbolo != '+' && simbolo != '-' && simbolo != '*' && simbolo != '/') {
		printf("Operador no valido. Intente de nuevo (+, -, *, /):\n");
		while (getchar() != '\n'); 
		scanf_s(" %c", &simbolo, 1);
	}

	operacion = char_a_operador(simbolo);

	printf("Introduzca operando derecho\n");
	while (scanf_s("%lld", &operando_der)!= 1) {
		printf("Debe introducir un número:\n");
		while (getchar() != '\n');
	}

	long long resultado = resuelve_operacion(
		operando_izq,
		operando_der,
		operacion);

	if (resultado != (long long)FLT_MAX) {											/* cte FTL_MAX sirve como centinela */
		printf("%6lld %s %6lld = %6lld\n",
			operando_izq,
			operador_str(operacion),
			operando_der,
			resultado);
	}
	else {
		fprintf(stderr, "No se pudo resolver la operación %lld %s %lld\n",
			operando_izq, operador_str(operacion), operando_der);
	}


	return 0;
}