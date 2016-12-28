#include <stdbool.h>
#include <allegro.h>
#include "movimientos_alfil.h"
#include "movimientos_caballo.h"
#include "movimientos_peon.h"
#include "movimientos_reina.h"
#include "movimientos_torre.h"

#define LADO 8

bool es_amigo_de_rey(char rey, char otro) {
	return (rey == 'r')? otro == 'w' || otro == 'a' || otro == 'r' || otro == 't' || otro == 'c' || otro == 'p':
			otro == 'W' || otro == 'A' || otro == 'R' || otro == 'T' || otro == 'C' || otro == 'P';
}



// pasa que en fila_destino no hay nada, todavia no se movio
bool me_hacen_jaque(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i,j, f_rey_b, c_rey_b, f_rey_n, c_rey_n;
	bool es_jaque = false;
	char pieza_aux = campo[fila_destino][columna_destino], rey_original = ' ';
	if(campo[fila_origen][columna_origen] == 'r') {
		campo[fila_destino][columna_destino] = 'r';
		rey_original = 'r';
		f_rey_b = fila_destino;
		c_rey_b = columna_destino;
	} else {
		campo[fila_destino][columna_destino] = 'R';
		rey_original = 'R';
		f_rey_n = fila_destino;
		c_rey_n = columna_destino;
	}
	campo[fila_origen][columna_origen] = ' ';

	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] != ' ' && !es_amigo_de_rey(campo[fila_destino][columna_destino], campo[i][j])) {
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
	campo[fila_destino][columna_destino] = pieza_aux;
	campo[fila_origen][columna_origen] = rey_original;
	return es_jaque;
}

bool movimiento_permitido_rey(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return ((fila_origen + 1 == fila_destino && columna_origen == columna_destino) ||
		    (fila_origen - 1 == fila_destino && columna_origen == columna_destino) ||
		    (columna_origen + 1 == columna_destino && fila_origen == fila_destino) ||
		    (columna_origen - 1 == columna_destino && fila_origen == fila_destino) ||
		    (fila_origen + 1 == fila_destino && columna_origen + 1 == columna_destino) ||
		    (fila_origen - 1 == fila_destino && columna_origen - 1 == columna_destino) ||
		    (fila_origen + 1 == fila_destino && columna_origen - 1 == columna_destino) ||
		    (fila_origen - 1 == fila_destino && columna_origen + 1 == columna_destino)) &&
			!me_hacen_jaque(fila_origen, columna_origen, fila_destino, columna_destino, campo) &&
			!es_amigo_de_rey(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}


bool es_jaque_rey(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	bool es_jaque = false;
		if(pieza == 'r' && movimiento_permitido_rey(fila_destino, columna_destino, f_rey_n, c_rey_n, campo)) {
			es_jaque = true;
		}
		if(pieza == 'R' && movimiento_permitido_rey(fila_destino, columna_destino, f_rey_b, c_rey_b, campo)) {
			es_jaque = true;
		}
	return es_jaque;
}

bool es_jaque_mate(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	bool es_mate = false;

	if(fila_origen + 1 != 8 && fila_origen - 1 != -1 && columna_origen - 1 != -1 && columna_origen + 1 != 8) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen -1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen + 1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen -1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen + 1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen -1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen + 1, campo);
	}

	if(fila_origen + 1 == 8 && fila_origen - 1 != -1 && columna_origen - 1 != -1 && columna_origen + 1 != 8) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen -1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen + 1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen -1, campo) &&
				  me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen + 1, campo);
	}

	if(fila_origen - 1 == -1 && fila_origen + 1 != 8 && columna_origen - 1 != -1 && columna_origen + 1 != 8) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen - 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen + 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen -1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen + 1, campo);
	}

	if(columna_origen + 1 == 8 && columna_origen - 1 != -1 && fila_origen + 1 != 8 && fila_origen -1 != -1) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen -1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen -1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen -1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo);
	}

	if(columna_origen - 1 == -1 && columna_origen + 1 != 8 && fila_origen + 1 != 8 && fila_origen -1 != -1) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen + 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen + 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen + 1, campo);
	}

	if(columna_origen - 1 == -1 && fila_origen - 1 == -1) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen + 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen + 1, campo);
	}

	if(columna_origen + 1 == 8 && fila_origen - 1 == -1) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen - 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen - 1, campo);
	}

	if(columna_origen + 1 == 8 && fila_origen + 1 == 8) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen - 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen + 1, columna_origen, campo);
	}

	if(columna_origen - 1 == -1 && fila_origen + 1 == 8) {
		es_mate = me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen - 1, columna_origen + 1, campo) &&
				me_hacen_jaque(fila_origen, columna_origen, fila_origen, columna_origen + 1, campo);
	}
	return es_mate;
}



