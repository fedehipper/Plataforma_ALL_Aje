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

bool es_superior_a_rey(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna, campo) == 'r') {
		return fila_destino == fila_origen - 1;
	} else {
		return fila_destino - 1 == fila_origen;
	}
}

bool es_inferior_a_rey(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna, campo) == 'r') {
		return fila_destino - 1 == fila_origen;
	} else {
		return fila_destino == fila_origen - 1;
	}
}

bool es_izquierda_a_rey(int fila, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila, columna_origen, campo) == 'r') {
		return columna_origen == columna_destino + 1;
	} else {
		return columna_origen - 1 == columna_destino;
	}
}

bool es_derecha_a_rey(int fila, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila, columna_origen, campo) == 'r') {
		return columna_origen + 1 == columna_destino;
	} else {
		return columna_origen == columna_destino - 1;
	}
}

bool es_superior_derecho_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen + 1 == columna_destino && fila_origen - 1 == fila_destino;
	} else {
		return columna_origen - 1 == columna_destino && fila_origen + 1 == fila_destino;
	}
}

bool es_superior_izquierdo_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen == columna_destino + 1 && fila_destino == fila_origen - 1;
	} else {
		return columna_origen == columna_destino - 1 && fila_destino == fila_origen + 1;
	}
}

bool es_inferior_derecho_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen + 1 == columna_destino && fila_destino - 1 == fila_origen;
	} else {
		return columna_origen - 1 == columna_destino && fila_destino + 1 == fila_origen;
	}
}

bool es_inferior_izquierdo_a_rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_rey(fila_origen, columna_origen, campo) == 'r') {
		return columna_origen == columna_destino + 1 && fila_destino - 1 == fila_origen;
	} else {
		return columna_origen == columna_destino - 1 && fila_destino + 1 == fila_origen;
	}
}


bool movimiento_permitido_rey(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	bool condicion = false;
	condicion = es_superior_a_rey(fila_origen, fila_destino, columna_origen, campo) ||
				es_inferior_a_rey(fila_origen, fila_destino, columna_origen, campo) ||
				es_derecha_a_rey(fila_origen, columna_origen, columna_destino, campo) ||
				es_izquierda_a_rey(fila_origen, columna_origen, columna_destino, campo) ||
				es_superior_izquierdo_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo) ||
				es_superior_derecho_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo) ||
				es_inferior_derecho_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo) ||
				es_inferior_izquierdo_a_rey(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	if(condicion) {
		return !es_amigo_de_rey(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
	} else return false;
}


