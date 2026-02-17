#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define TOTAL_CARTAS 40

typedef enum {
	PALO_BASTOS = 0,
	PALO_COPAS,
	PALO_ESPADAS,
	PALO_OROS,
	PALO_NINGUNO,
	PALO_COUNT
} palo_t;

typedef struct {
	unsigned int num_;
	palo_t palo_;
} carta_t;

const char* palo_str(palo_t palo) {
	static const char* nombres[] = { "Bastos", "Copas", "Espadas", "Oros", "Ninguno" };
	if (palo < 0 || palo >= PALO_COUNT) return "Desconocido";
	return nombres[palo];
}

const char* carta_str(carta_t carta) {
	static char buffer[32];
	snprintf(buffer, sizeof(buffer), "%u de %s", carta.num_, palo_str(carta.palo_));
	return buffer;
}

void carta_clear(carta_t* c) {
	c->palo_ = PALO_NINGUNO;
	c->num_ = 0;
}

void carta_set(carta_t* c, unsigned int num, palo_t palo) {
	c->num_ = num;
	c->palo_ = palo;
}

void carta_intercambiar(carta_t* a, carta_t* b) {
	carta_t temp = *a;
	*a = *b;
	*b = temp;
}

void baraja_mezclar(carta_t* baraja, int tam) {
	srand((unsigned int)time(NULL));

	for (int i = tam - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		carta_intercambiar(&baraja[i], &baraja[j]);
	}
}

int main(void) {
	carta_t baraja[TOTAL_CARTAS];
	int i, p, contador = 0;

	for (p = 0; p < 4; p++) {
		for (unsigned int n = 1; n <= 10; n++) {
			carta_set(&baraja[contador], n, (palo_t)p);
			contador++;
		}
	}

	printf("Baraja Nueva:\n\n");

	for (i = 0; i < TOTAL_CARTAS; i++) {
		printf("[%02d] %s\n", i + 1, carta_str(baraja[i]));
	}

	printf("\nBaraja Mezclada:\n\n");

	baraja_mezclar(baraja, TOTAL_CARTAS);

	for (int i = 0; i < TOTAL_CARTAS; i++) {
		printf("[%02d] %s\n", i + 1, carta_str(baraja[i]));
	}

	return 0;
}