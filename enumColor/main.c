#include <stdio.h>
#include<locale.h>

typedef	enum {
	ROJO = 0,
	VERDE,
	AMARILLO,
	MORADO
} color;

typedef enum {
	FALSE = 0,
	TRUE = 1
} BOOL;

void foo(color c) {
	printf("Color: %d\n", c);
}

void detector_de_mentiras(BOOL b) {
	printf("Detección: %d\n", b);
}

int main() {
	setlocale(LC_ALL, "spanish");
	foo(4);
	detector_de_mentiras(1);
}