#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LADO 8
#define CARACTER_A_ENTERO 97


char color_peon(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_inmediato_siguiente(int fila_origen, int fila_destino, int columna_origen, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 1 == fila_destino;
	} else {
		return fila_origen + 1 == fila_destino;
	}
}

bool es_siguiente_saltando_uno(int fila_origen, int fila_destino, int columna_origen, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 2 == fila_destino;
	} else {
		return fila_origen + 2 == fila_destino;
	}
}

bool es_superior_derecho(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 1 == fila_destino && columna_origen + 1 == columna_destino;
	} else {
		return fila_origen + 1 == fila_destino && columna_origen - 1 == columna_destino;
	}
}

bool es_superior_izquierda(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 1 == fila_destino && columna_origen - 1 == columna_destino;
	} else {
		return fila_origen + 1 == fila_destino && columna_origen + 1 == columna_destino;
	}
}

bool puede_ir_al_inmediato_siguiente(int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return campo[fila_destino][columna_destino] == ' ';
}

bool puede_ir_al_siguiente_saltando_uno(int fila_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return campo[fila_destino][columna_destino] == ' ' && (fila_origen == 6 || fila_origen == 1);
}

bool puede_ir_al_superior(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	char objetivo = campo[fila_destino][columna_destino];
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return objetivo != ' ' ||( objetivo > 65 && objetivo < 97); // 65 en adelante NEGRO, 97 en adelante BLANCO
	} else {
		return objetivo != ' ' || objetivo > 97;
	}
}
bool movimiento_permitido(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(es_inmediato_siguiente(fila_origen, fila_destino, columna_origen, campo)) {
		return puede_ir_al_inmediato_siguiente(fila_destino, columna_destino, campo);
	} else if(es_siguiente_saltando_uno(fila_origen, fila_destino, columna_origen, campo)) {
		return puede_ir_al_siguiente_saltando_uno(fila_origen, fila_destino, columna_destino, campo);
	} else if(es_superior_derecho(fila_origen, fila_destino, columna_origen, columna_destino, campo)) {
		return puede_ir_al_superior(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	} else if(es_superior_izquierda(fila_origen, fila_destino, columna_origen, columna_destino, campo)) {
		return puede_ir_al_superior(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	} else
		return false;
}



