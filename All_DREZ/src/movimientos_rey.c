#include <stdbool.h>
#include <allegro.h>
#include "movimientos_alfil.h"
#include "movimientos_caballo.h"
#include "movimientos_peon.h"
#include "movimientos_reina.h"
#include "movimientos_torre.h"
#include "comportamiento_comun_piezas.h"

#define LADO 8

bool es_amigo_de_rey(char rey, char p) {
	return (rey =='r')? p =='w'||p =='a'||p =='r'||p =='t'||p =='c'||p =='p': p =='W'||p =='A'||p =='R'||p =='T'||p =='C'||p =='P';
}

bool movimiento_rey_sin_reestricciones(int fila_o, int columna_o, int fila_d, int columna_d) {
	return ((fila_o + 1 == fila_d && columna_o == columna_d) || (fila_o - 1 == fila_d && columna_o == columna_d) ||
		(columna_o + 1 == columna_d && fila_o == fila_d) || (columna_o - 1 == columna_d && fila_o == fila_d) ||
		(fila_o + 1 == fila_d && columna_o + 1 == columna_d) || (fila_o - 1 == fila_d && columna_o - 1 == columna_d) ||
		(fila_o + 1 == fila_d && columna_o - 1 == columna_d) || (fila_o - 1 == fila_d && columna_o + 1 == columna_d));
}

bool me_hacen_jaque(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	int i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n;
	bool es_jaque = false;
	char pieza_aux = campo[fila_d][columna_d], rey_original = ' ';
	if(campo[fila_o][columna_o] == 'r') {
		campo[fila_d][columna_d] = 'r';
		rey_original = 'r';
		f_rey_b = fila_d;
		c_rey_b = columna_d;
	} else {
		campo[fila_d][columna_d] = 'R';
		rey_original = 'R';
		f_rey_n = fila_d;
		c_rey_n = columna_d;
	}
	campo[fila_o][columna_o] = ' ';
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] != ' ' && !es_amigo_de_rey(campo[fila_d][columna_d], campo[i][j])) {
				switch(campo[i][j]) {
					case 'p': case 'P': if(es_jaque_peon(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'a': case 'A': if(es_jaque_alfil(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n,campo)) es_jaque = true; break;
					case 't': case 'T': if(es_jaque_torre(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'c': case 'C': if(es_jaque_caballo(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'w': case 'W': if(es_jaque_reina(campo[i][j], i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
					case 'R': case 'r': if(movimiento_rey_sin_reestricciones(i, j, fila_d, columna_d)) es_jaque = true; break;
				}
				if (es_jaque) break;
			}
		}
	}
	campo[fila_d][columna_d] = pieza_aux;
	campo[fila_o][columna_o] = rey_original;
	return es_jaque;
}

bool movimiento_permitido_rey(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]) {
	return movimiento_rey_sin_reestricciones(fila_o, columna_o, fila_d, columna_d) &&
		!me_hacen_jaque(fila_o, columna_o, fila_d, columna_d, campo) && !es_amigo_de_rey(campo[fila_o][columna_o], campo[fila_d][columna_d]);
}

bool es_jaque_rey(char pieza, int fila_d, int columna_d, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	return ((pieza == 'r' && movimiento_permitido_rey(fila_d, columna_d, f_rey_n, c_rey_n, campo))) ||
		((pieza == 'R' && movimiento_permitido_rey(fila_d, columna_d, f_rey_b, c_rey_b, campo)));
}
