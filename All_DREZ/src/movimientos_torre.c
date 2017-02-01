#include <stdbool.h>
#include "movimientos_peon.h"
#include "movimientos_caballo.h"
#include "movimientos_reina.h"
#include "movimientos_rey.h"
#include "movimientos_alfil.h"

#define LADO 8

bool es_amigo_de_torre(char t, char p) {
	return t == 't'? p == 'w'||p == 'a'||p == 'r'||p == 'p'||p == 'c'||p == 't' : p == 'W'||p == 'A'||p == 'R'||p == 'P'||p == 'C'||p == 'T';
}

bool es_abajo_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	return (campo[fila_o][columna_o] == 't') ? fila_o < fila_d && columna_o == columna_d : fila_o > fila_d && columna_o == columna_d;
}

bool es_arriba_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	return (campo[fila_o][columna_o] == 't') ? fila_o > fila_d && columna_o == columna_d : fila_o < fila_d && columna_o == columna_d;
}

bool es_a_la_izquierda_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	return (campo[fila_o][columna_o] == 't') ? columna_o > columna_d && fila_o == fila_d : columna_o < columna_d && fila_o == fila_d;
}

bool es_a_la_derecha_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	return (campo[fila_o][columna_o] == 't') ? columna_o < columna_d && fila_o == fila_d : columna_o > columna_d && fila_o == fila_d;
}

bool puede_ir_arriba_torre(int fila_o, int fila_d, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(campo[fila_o][columna] == 't') {
		distancia = fila_o - fila_d;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_o - i][columna] != ' ') break;
		}
	} else {
		distancia = fila_d - fila_o;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_o + i][columna] != ' ') break;
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_o][columna], campo[fila_d][columna]);
}

bool puede_ir_abajo_torre(int fila_o, int fila_d, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(campo[fila_o][columna] == 't') {
		distancia = fila_d - fila_o;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_o + i][columna] != ' ') break;
		}
	} else {
		distancia = fila_o - fila_d;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_o - i][columna] != ' ') break;
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_o][columna], campo[fila_d][columna]);
}

bool puede_ir_izquierda_torre(int columna_o, int columna_d, int fila, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(campo[fila][columna_o] == 't') {
		distancia = columna_o - columna_d;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_o - i] != ' ') break;
		}
	} else {
		distancia = columna_d - columna_o;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_o + i] != ' ') break;
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila][columna_o], campo[fila][columna_d]);
}

bool puede_ir_derecha_torre(int columna_o, int columna_d, int fila, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(campo[fila][columna_o] == 't') {
		distancia = columna_d - columna_o;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_o + i] != ' ') break;
		}
	} else {
		distancia = columna_o - columna_d;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_o - i] != ' ') break;
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila][columna_o], campo[fila][columna_d]);
}

bool movimiento_permitido_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	if(es_arriba_de_torre(fila_o, columna_o, fila_d, columna_d, campo)) return puede_ir_arriba_torre(fila_o, fila_d, columna_o, campo);
	else if(es_abajo_de_torre(fila_o, columna_o, fila_d, columna_d, campo)) return puede_ir_abajo_torre(fila_o, fila_d, columna_o, campo);
	else if(es_a_la_derecha_de_torre(fila_o, columna_o, fila_d, columna_d, campo)) return puede_ir_derecha_torre(columna_o, columna_d, fila_o, campo);
	else if(es_a_la_izquierda_de_torre(fila_o, columna_o, fila_d,  columna_d, campo)) return puede_ir_izquierda_torre(columna_o, columna_d, fila_o, campo);
	else return false;
}

bool es_jaque_torre(char pieza, int fila_d, int columna_d, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	return (pieza == 't' && movimiento_permitido_torre(fila_d, columna_d, f_rey_n, c_rey_n, campo)) ||
		(pieza == 'T' && movimiento_permitido_torre(fila_d, columna_d, f_rey_b, c_rey_b, campo));
}

bool si_se_mueve_es_jaque_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n) {
	int i,j;
	char pieza = campo[fila_o][columna_o], pieza_destino = campo[fila_d][columna_d];
	bool es_jaque = false;
	// hago que se mueva al destino y veo si sigue el jaque
	campo[fila_o][columna_o] = ' ';
	campo[fila_d][columna_d] = pieza;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(!es_amigo_de_torre(pieza, campo[i][j])) {
				switch(campo[i][j]) {
					case 'p': case 'P': if(es_jaque_peon(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'a': case 'A': if(es_jaque_alfil(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n,campo)) es_jaque = true; break;
					case 't': case 'T': if(es_jaque_torre(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'c': case 'C': if(es_jaque_caballo(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'w': case 'W': if(es_jaque_reina(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
				}
				if (es_jaque) break;
			}
		}
	}
	// hago que aparezca
	campo[fila_o][columna_o] = pieza;
	campo[fila_d][columna_d] = pieza_destino;
	return es_jaque;
}
