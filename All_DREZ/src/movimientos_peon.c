#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "movimientos_caballo.h"
#include "movimientos_reina.h"
#include "movimientos_rey.h"
#include "movimientos_torre.h"
#include "movimientos_alfil.h"

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

bool es_jaque_peon(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	bool es_jaque = false;
		if(pieza == 'p' && movimiento_permitido_peon(fila_destino, columna_destino, f_rey_n, c_rey_n, campo)) {
			es_jaque = true;
		}
		if(pieza == 'P' && movimiento_permitido_peon(fila_destino, columna_destino, f_rey_b, c_rey_b, campo)) {
			es_jaque = true;
		}
	return es_jaque;
}

bool si_se_mueve_es_jaque_peon(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n) {
	int i,j;
	char pieza = campo[fila_origen][columna_origen], pieza_destino = campo[fila_destino][columna_destino];
	bool es_jaque = false;
	// hago que se mueva al destino y veo si sigue el jaque
	campo[fila_origen][columna_origen] = ' ';
	campo[fila_destino][columna_destino] = pieza;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(!es_amigo_de_peon(pieza, campo[i][j])) {
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
	campo[fila_origen][columna_origen] = pieza;
	campo[fila_destino][columna_destino] = pieza_destino;
	return es_jaque;
}


