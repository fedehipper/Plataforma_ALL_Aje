#include <stdbool.h>
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

bool movimiento_permitido_rey(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return ((fila_origen + 1 == fila_destino && columna_origen == columna_destino) ||
		    (fila_origen - 1 == fila_destino && columna_origen == columna_destino) ||
		    (columna_origen + 1 == columna_destino && fila_origen == fila_destino) ||
		    (columna_origen - 1 == columna_destino && fila_origen == fila_destino) ||
		    (fila_origen + 1 == fila_destino && columna_origen + 1 == columna_destino) ||
		    (fila_origen - 1 == fila_destino && columna_origen - 1 == columna_destino) ||
		    (fila_origen + 1 == fila_destino && columna_origen - 1 == columna_destino) ||
		    (fila_origen - 1 == fila_destino && columna_origen + 1 == columna_destino)) &&
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

//bool me_hacen_jaque(int fila_origen, int columna_origen, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
//	int i,j;
//	bool es_jaque = false;
//	for(i = 0 ; i < LADO ; i++) {
//		for(j = 0 ; j < LADO ; j++) {
//			if(campo[i][j] != ' ' && !es_amigo_de_rey(campo[fila_origen][columna_origen], campo[i][j])) {
//				switch(campo[i][j]) {
//					case 'p':
//					case 'P': if(es_jaque_peon(i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
//					break;
//					case 'a':
//					case 'A': if(es_jaque_alfil(i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n,campo)) es_jaque = true;
//					break;
//					case 't':
//					case 'T': if(es_jaque_torre(i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
//					break;
//					case 'c':
//					case 'C': if(es_jaque_caballo(i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
//					break;
//					case 'w':
//					case 'W': if(es_jaque_reina(i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true;
//					break;
//				}
//				if (es_jaque) break;
//			}
//
//		}
//	}
//	return es_jaque;
//}
