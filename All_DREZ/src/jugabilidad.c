#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"
#include "movimientos_torre.h"
#include "movimientos_rey.h"
#include "movimientos_alfil.h"
#include "movimientos_reina.h"
#include "movimientos_caballo.h"

#define LADO 8

void mover_pieza_a_destino(char pieza, int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {

	if(campo[fila_origen][columna_origen] != ' ' && columna_destino != 8 && fila_destino != 8 && columna_origen != 8 && fila_origen != 8) {

		switch(campo[fila_origen][columna_origen]) {
			case 'p':
			case 'P': {
				if(movimiento_permitido_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
					campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
					campo[fila_origen][columna_origen] = ' ';
				}
			}
			break;
			case 'T':
			case 't': {
				if(movimiento_permitido_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
					campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
					campo[fila_origen][columna_origen] = ' ';
				}
			}
			break;
			case 'r':
			case 'R': {
				if(movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
					campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
					campo[fila_origen][columna_origen] = ' ';
				}
			}
			break;
			case 'a':
			case 'A': {
				if(movimiento_permitido_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
					campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
					campo[fila_origen][columna_origen] = ' ';
				}
			}
			break;
			case 'w':
			case 'W': {
				if(movimiento_permitido_reina(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
					campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
					campo[fila_origen][columna_origen] = ' ';
				}
			}
			break;
			case 'c':
			case 'C':{
				if(movimiento_permitido_caballo(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
					campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
					campo[fila_origen][columna_origen] = ' ';
				}
			}

		}
	}
}

bool misma_coordenada(int fila, int columna, int nueva_fila, int nueva_columna) {
	return fila == nueva_fila && columna == nueva_columna;
}

char obtener_pieza(int fila, int columna, char campo[LADO][LADO]) {
	if(fila != 8 && columna != 8)
		return campo[fila][columna];
	else
		return '_';
}

bool hay_pieza(int fila, int columna, char campo[LADO][LADO]) {
	return fila != 8 && columna != 8 && campo[fila][columna] != ' ';
}

bool es_pieza_blanca(int fila, int columna, char campo[LADO][LADO]) {
	char pieza = campo[fila][columna];
	return pieza == 'w' || pieza == 'a' || pieza == 'r' || pieza == 't' || pieza == 'c' || pieza == 'p';
}

void seleccionar(char campo[LADO][LADO]) {
	int fila = 0, columna = 0, fila_origen = 0, fila_destino = 0, columna_origen = 0, columna_destino = 0, clic = 0, tecla = 0;
	char pieza = ' ';

	while(tecla != KEY_ESC) {
		rest(75);

		if(pieza != '_') {
			if(clic == 1) {
				fila_origen = fila;
				columna_origen = columna;
			}

			if(clic > 1 && !misma_coordenada(fila_origen, columna_origen, fila, columna)) {
				fila_destino = fila;
				columna_destino = columna;
				mover_pieza_a_destino(pieza, fila_origen, fila_destino, columna_origen, columna_destino, campo);
				draw_selector_cuadrado(fila_destino, columna_destino, campo);
				draw_cuadrado(fila_origen, columna_origen, campo);
				re_draw(campo);
				clic = 0;
			}
		}

		if(mouse_b & 1) {
			fila = (mouse_y - 11) / 80;
			columna = (mouse_x - 11) / 80;
			if(hay_pieza(fila, columna, campo)) {
				draw_selector_cuadrado(fila, columna, campo);
			}
			pieza = obtener_pieza(fila, columna, campo);
			if(pieza != '_') {
				clic += 1;
			}
		}

		if(mouse_b & 2) {
			re_draw(campo);
			clic = 0;
		}

		if(keypressed()) tecla = readkey() >> 8;
	}

}

