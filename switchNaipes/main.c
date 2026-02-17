/**
* @file naipes.c
* @brief Codificación para las cartas de la baraja española
* @details
* - creado 14/02/2022
* - última actualización 09/02/2026
* @author Pablo San Segundo, curso Informática Industrial, ETSIDI UPM
**/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************
* Estructuras de datos
****************/

typedef enum {
	PALO_BASTOS = 0,
	PALO_COPAS,
	PALO_ESPADAS,
	PALO_OROS,
	PALO_NINGUNO,
	PALO_COUNT			/* Este valor se usa para validar el rango del enum */
} palo_t;

typedef struct carta_t {
	unsigned int num_;
	palo_t palo_;
} carta_t;


/****************
* Servicios
****************/

/**
* @brief Convierte un palo a su representación en cadena usando un switch
* @param palo El palo a convertir
* @details
*  - Fácil de entender y mantener, ya que cada caso está claramente definido.
**/
const char* palo_str_patron_con_switch(palo_t palo) {
	switch (palo) {
	case PALO_BASTOS:	return "Bastos";
	case PALO_COPAS:	return "Copas";
	case PALO_ESPADAS:	return "Espadas";
	case PALO_OROS:		return "Oros";
	case PALO_NINGUNO:	return "Ninguno";
	default:			return "Desconocido";
	}
}

/**
* @brief Convierte un palo a su representación en cadena usando un array de cadenas
* @param palo El palo a convertir
* @details
*  - Evita múltiples comparaciones y saltos (más directo que switch).
*  - Solo válido si el enum es contiguo y empieza en 0.
*  - static: el array se crea una vez y se reutiliza.
**/
const char* palo_str_patron_con_array(palo_t palo) {

	static const char* nombres[] = {
		"Bastos",
		"Copas",
		"Espadas",
		"Oros",
		"Ninguno"
	};
	return nombres[palo];
}

/**
* @brief Convierte una carta a su representación en cadena

* @param carta La carta a convertir
* @details
* - Usa snprintf para evitar desbordamientos de buffer.
* - Implementación con buffer estático: no reentrante / no thread-safe.
**/

const char* carta_str(carta_t carta) {
	static char buffer[32];					/* tiene que ser estático */

	/* sprintf es legacy */
	snprintf(buffer, sizeof(buffer), "%u de %s",
		carta.num_, palo_str_patron_con_switch(carta.palo_));
	return buffer;
}

void carta_clear(carta_t* n) {
	n->palo_ = PALO_NINGUNO;
	n->num_ = 0;
}

void carta_set(carta_t* c, unsigned int num, palo_t palo) {
	c->num_ = num;
	c->palo_ = palo;
}

/******************
* TESTS UNITARIOS
******************/
int main(void) {

	carta_t mi_carta = { 1, PALO_COPAS };
	puts(carta_str(mi_carta));

	carta_clear(&mi_carta);
	puts(carta_str(mi_carta));

	mi_carta = (carta_t){ 2, PALO_ESPADAS };
	puts(carta_str(mi_carta));

	mi_carta.num_ = 3;
	mi_carta.palo_ = PALO_OROS;
	puts(carta_str(mi_carta));

	carta_set(&mi_carta, 4, PALO_BASTOS);
	puts(carta_str(mi_carta));

	return 0;
}