#include <stdio.h>

void foo(const char cadena[])
{
	printf("%zu\n", sizeof(cadena));
}

int main() {
	char cadena[] = "Hola";
	char cadena2[] = { 'H', 'o', 'l', 'a', '\0' };
	printf("%zu %zu\n", sizeof(cadena), sizeof(cadena2));

	foo("hola");

	return 0;
}