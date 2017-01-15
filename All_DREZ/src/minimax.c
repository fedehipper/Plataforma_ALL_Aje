#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LADO 8

enum {MAX, MIN};

typedef struct movimiento {
	int tipo_nodo; // MAX o MIN
	int valor_nodo; // depende de max o min, cual va a ser el mejor movimiento
	int matriz[LADO][LADO]; // matriz de como queda el movimiento
	struct movimiento *izq;
	struct movimiento *der;
} t_nodo;
