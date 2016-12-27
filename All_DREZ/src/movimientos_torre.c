#include <stdbool.h>
#include "movimientos_peon.h"
#include "movimientos_caballo.h"
#include "movimientos_reina.h"
#include "movimientos_rey.h"
#include "movimientos_alfil.h"

#define LADO 8

bool es_amigo_de_torre(char torre, char otro) {
	return torre == 't'? otro == 'w' || otro == 'a' || otro == 'r' || otro == 'p' || otro == 'c' || otro == 't' :
		   otro == 'W' || otro == 'A' || otro == 'R' || otro == 'P' || otro == 'C' || otro == 'T';
}

char color_torre(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_abajo_de_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return fila_origen < fila_destino && columna_origen == columna_destino;
	} else {
		return fila_origen > fila_destino && columna_origen == columna_destino;
	}
}

bool es_arriba_de_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return fila_origen > fila_destino && columna_origen == columna_destino;
	} else {
		return fila_origen < fila_destino && columna_origen == columna_destino;
	}
}

bool es_a_la_izquierda_de_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return columna_origen > columna_destino && fila_origen == fila_destino;
	} else {
		return columna_origen < columna_destino && fila_origen == fila_destino;
	}
}

bool es_a_la_derecha_de_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return columna_origen < columna_destino && fila_origen == fila_destino;
	} else {
		return columna_origen > columna_destino && fila_origen == fila_destino;
	}
}

bool puede_ir_arriba_torre(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila_origen, columna, campo) == 't') {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
}

bool puede_ir_abajo_torre(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila_origen, columna, campo) == 't') {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
}


bool puede_ir_izquierda_torre(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila, columna_origen, campo) == 't') {
		distancia = columna_origen - columna_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen - i] != ' ') {
				break;
			}
		}
	} else {
		distancia = columna_destino - columna_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen + i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
}

bool puede_ir_derecha_torre(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila, columna_origen, campo) == 't') {
		distancia = columna_destino - columna_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen + i] != ' ') {
				break;
			}
		}
	} else {
		distancia = columna_origen - columna_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen - i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
}


bool movimiento_permitido_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(es_arriba_de_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_arriba_torre(fila_origen, fila_destino, columna_origen, campo);
	} else if(es_abajo_de_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_abajo_torre(fila_origen, fila_destino, columna_origen, campo);
	} else if(es_a_la_derecha_de_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_derecha_torre(columna_origen, columna_destino, fila_origen, campo);
	} else if(es_a_la_izquierda_de_torre(fila_origen, columna_origen, fila_destino,  columna_destino, campo)) {
		return puede_ir_izquierda_torre(columna_origen, columna_destino, fila_origen, campo);
	} else
		return false;
}

bool es_jaque_torre(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	bool es_jaque = false;
		if(pieza == 't' && movimiento_permitido_torre(fila_destino, columna_destino, f_rey_n, c_rey_n, campo)) {
			es_jaque = true;
		}
		if(pieza == 'T' && movimiento_permitido_torre(fila_destino, columna_destino, f_rey_b, c_rey_b, campo)) {
			es_jaque = true;
		}
	return es_jaque;
}

bool si_se_mueve_es_jaque_torre(int fila, int columna, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n) {
	int i,j;
	char pieza = campo[fila][columna];
	bool es_jaque = false;
	// hago que desaparezca
	campo[fila][columna] = ' ';
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(!es_amigo_de_torre(pieza, campo[i][j])) {
				switch(campo[i][j]) {
					case 'p': if(es_jaque_peon('p', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'P': if(es_jaque_peon('P', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'a': if(es_jaque_alfil('a', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n,campo)) es_jaque = true;
					break;
					case 'A': if(es_jaque_alfil('A', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n,campo)) es_jaque = true;
					break;
					case 't': if(es_jaque_torre('t', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'T': if(es_jaque_torre('T', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'c': if(es_jaque_caballo('c', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'C': if(es_jaque_caballo('C', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'w': if(es_jaque_reina('w', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
					case 'W': if(es_jaque_reina('W', i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
					break;
				}
				if (es_jaque) break;
			}
		}
	}
	// hago que aparezca
	campo[fila][columna] = pieza;
	return es_jaque;
}





