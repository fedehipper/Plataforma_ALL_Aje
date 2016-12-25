#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LADO 8

bool es_amigo_de_peon(char peon, char otro) {
	return (peon == 'p')? otro == 'w' || otro == 'a' || otro == 'r' || otro == 't' || otro == 'c' || otro == 'p':
			otro == 'W' || otro == 'A' || otro == 'R' || otro == 'T' || otro == 'C' || otro == 'P';
}

char color_peon(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_inmediato_siguiente_a_peon(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 1 == fila_destino && columna_origen == columna_destino;
	} else {
		return fila_origen + 1 == fila_destino && columna_origen == columna_destino;
	}
}

bool es_siguiente_saltando_uno_a_peon(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 2 == fila_destino && columna_origen == columna_destino && campo[fila_origen - 1][columna_origen] == ' ';
	} else {
		return fila_origen + 2 == fila_destino && columna_origen == columna_destino && campo[fila_origen + 1][columna_origen] == ' ';
	}
}

bool es_superior_derecho_de_peon(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 1 == fila_destino && columna_origen + 1 == columna_destino;
	} else {
		return fila_origen + 1 == fila_destino && columna_origen - 1 == columna_destino;
	}
}

bool es_superior_izquierda_de_peon(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_peon(fila_origen, columna_origen, campo) == 'p') {
		return fila_origen - 1 == fila_destino && columna_origen - 1 == columna_destino;
	} else {
		return fila_origen + 1 == fila_destino && columna_origen + 1 == columna_destino;
	}
}

bool puede_ir_al_inmediato_siguiente_peon(int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return campo[fila_destino][columna_destino] == ' ';
}

bool puede_ir_al_siguiente_saltando_uno_peon(int fila_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return campo[fila_destino][columna_destino] == ' ' && (fila_origen == 6 || fila_origen == 1);
}

bool puede_ir_al_superior_peon(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	char objetivo = campo[fila_destino][columna_destino];
	return objetivo != ' ' && !es_amigo_de_peon(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}

bool movimiento_permitido_peon(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(es_superior_izquierda_de_peon(fila_origen, fila_destino, columna_origen, columna_destino, campo)) {
		return puede_ir_al_superior_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	}
	if(es_superior_derecho_de_peon(fila_origen, fila_destino, columna_origen, columna_destino, campo)) {
		return puede_ir_al_superior_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo);
	}
	if(es_inmediato_siguiente_a_peon(fila_origen, fila_destino, columna_origen, columna_destino, campo)) {
		return puede_ir_al_inmediato_siguiente_peon(fila_destino, columna_destino, campo);
	}
	if(es_siguiente_saltando_uno_a_peon(fila_origen, fila_destino, columna_origen, columna_destino, campo)) {
		return puede_ir_al_siguiente_saltando_uno_peon(fila_origen, fila_destino, columna_destino, campo);
	} else return false;
}



