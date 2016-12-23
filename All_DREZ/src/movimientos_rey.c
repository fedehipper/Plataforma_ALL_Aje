#include <stdbool.h>

#define LADO 8

bool es_amigo_de_rey(char rey, char otro) {
	if(rey == 'r') {
		return otro == 'w' || otro == 'a' || otro == 'r' || otro == 't' || otro == 'c' || otro == 'p';
	} else {
		return otro == 'W' || otro == 'A' || otro == 'R' || otro == 'T' || otro == 'C' || otro == 'P';
	}
}

char color_rey(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_superior_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return fila_destino == fila_origen - 1 && columna_origen == columna_destino;
	} else {
		return fila_destino - 1 == fila_origen && columna_origen == columna_destino;
	}
}

bool es_inferior_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return fila_destino - 1 == fila_origen && columna_origen == columna_destino;
	} else {
		return fila_destino == fila_origen - 1 && columna_origen == columna_destino;
	}
}

bool es_izquierda_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen == columna_destino + 1 && fila_origen == fila_destino;
	} else {
		return columna_origen - 1 == columna_destino && fila_origen == fila_destino;
	}
}

bool es_derecha_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen + 1 == columna_destino && fila_origen == fila_destino;
	} else {
		return columna_origen == columna_destino - 1 && fila_origen == fila_destino;
	}
}

bool es_superior_derecha_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen + 1 == columna_destino && fila_destino == fila_origen - 1;
	} else {
		return columna_origen == columna_destino - 1 && fila_destino - 1 == fila_origen;
	}
}

bool es_superior_izquierda_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen == columna_destino + 1 && fila_destino == fila_origen - 1;
	} else {
		return columna_origen - 1 == columna_destino && fila_destino - 1 == fila_origen;
	}
}

bool es_inferior_derecha_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen + 1 == columna_destino && fila_destino - 1 == fila_origen;
	} else {
		return columna_origen == columna_destino - 1 && fila_destino == fila_origen - 1;
	}
}

bool es_inferior_izquierda_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen == columna_destino + 1 && fila_destino - 1 == fila_origen;
	} else {
		return columna_origen - 1 == columna_destino && fila_destino == fila_origen - 1;
	}
}

bool movimiento_permitido_rey(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	bool arriba = false, abajo = false, izquierda = false, derecha = false, superior_derecha = false, superior_izquierda = false,
		 inferior_derecha = false, inferior_izquierda = false;

	arriba = es_superior_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	abajo = es_inferior_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	izquierda = es_izquierda_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	derecha = es_derecha_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	superior_derecha = es_superior_derecha_a_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	superior_izquierda = es_superior_izquierda_a_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	inferior_derecha = es_inferior_derecha_a_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	inferior_izquierda = es_inferior_izquierda_a_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo);

	return (abajo || arriba || izquierda || derecha || superior_derecha || inferior_derecha || superior_izquierda || inferior_izquierda);
}


