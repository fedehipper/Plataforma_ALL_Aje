#include <stdbool.h>
#include <stdio.h>
#include "movimientos_peon.h"
#include "movimientos_caballo.h"
#include "movimientos_reina.h"
#include "movimientos_rey.h"
#include "movimientos_torre.h"


#define LADO 8

bool es_amigo_de_alfil(char alfil, char otro) {
	return (alfil == 'a') ? otro == 'w' || otro == 'a' || otro == 'r' || otro == 'p' || otro == 'c' || otro == 't':
			otro == 'W' || otro == 'A' || otro == 'R' || otro == 'P' || otro == 'C' || otro == 'T';
}

char color_alfil(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_superior_derecha_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen > fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1 ; i++) {
				if(fila_origen - i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen < fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = columna_origen;
			distancia_vertical = 7 - fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1 ; i++) {
				if(fila_origen + i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool es_superior_izquierda_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen > fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = columna_origen;
			distancia_vertical = fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1 ; i++) {
				if(fila_origen - i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen < fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = 7 - fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1; i++) {
				if(fila_origen + i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool es_inferior_derecha_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen < fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = 7 - fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1; i++) {
				if(fila_origen + i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen > fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = columna_origen;
			distancia_vertical = fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1; i++) {
				if(fila_origen - i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool es_inferior_izquierda_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen < fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = columna_origen;
			distancia_vertical = 7 - fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1 ; i++) {
				if(fila_origen + i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen > fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = fila_origen;
			distancia = (distancia_horizontal <= distancia_vertical) ? distancia_horizontal : distancia_vertical;
			for(i = 0 ; i < distancia + 1 ; i++) {
				if(fila_origen - i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool puede_ir_superior_derecha_alfil(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna_origen + i] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna_origen - i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_alfil(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}

bool puede_ir_superior_izquierda_alfil(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna_origen - i] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna_origen + i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_alfil(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}

bool puede_ir_inferior_derecha_alfil(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna_origen + i] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna_origen - i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_alfil(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}

bool puede_ir_inferior_izquierda_alfil(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna_origen - i] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna_origen + i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_alfil(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}

bool movimiento_permitido_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(es_superior_derecha_de_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_superior_derecha_alfil(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	} else if(es_superior_izquierda_de_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_superior_izquierda_alfil(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	} else if(es_inferior_derecha_de_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_inferior_derecha_alfil(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	} else if(es_inferior_izquierda_de_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
		return puede_ir_inferior_izquierda_alfil(fila_origen, fila_destino, columna_origen, columna_destino, campo);
	} else
		return false;
}

bool es_jaque_alfil(char pieza, int fila, int columna, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	bool es_jaque = false;
		if(pieza == 'a' && movimiento_permitido_alfil(fila, columna, f_rey_n, c_rey_n, campo)) {
			es_jaque = true;
		}
		if(pieza == 'A' && movimiento_permitido_alfil(fila, columna, f_rey_b, c_rey_b, campo)) {
			es_jaque = true;
		}
	return es_jaque;
}

bool si_se_mueve_es_jaque_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n) {
	int i, j;
	char pieza = campo[fila_origen][columna_origen], pieza_destino = campo[fila_destino][columna_destino];
	bool es_jaque = false;
	// hago que se mueva al destino y veo si sigue el jaque
	campo[fila_origen][columna_origen] = ' ';
	campo[fila_destino][columna_destino] = pieza;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(!es_amigo_de_alfil(pieza, campo[i][j])) {
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

