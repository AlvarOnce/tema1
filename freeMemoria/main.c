#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int* p = NULL;
	free(p);
	return 0;
}