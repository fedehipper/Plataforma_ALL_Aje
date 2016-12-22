#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "tablero_grafico.h"

#define LADO 8

void mover_pieza_a_destino(char pieza,int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(campo[fila_origen][columna_origen] != ' ' && columna_destino != 8 && fila_destino != 8 && columna_origen != 8 && fila_origen != 8) {
		campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
		campo[fila_origen][columna_origen] = ' ';
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
	return campo[fila][columna] != ' ';
}

void seleccionar(char campo[LADO][LADO]) {
	int fila = 0, columna = 0, fila_origen = 0, fila_destino = 0, columna_origen = 0, columna_destino = 0, clic = 0, tecla = 0;
	char pieza = ' ';

	while(tecla != KEY_ESC) {
		rest(100);

		if(clic == 1 && pieza != '_') {
			fila_origen = fila;
			columna_origen = columna;
		}

		if(clic > 1 && !misma_coordenada(fila_origen, columna_origen, fila, columna) && pieza != '_') {
			fila_destino = fila;
			columna_destino = columna;
			mover_pieza_a_destino(pieza, fila_origen, fila_destino, columna_origen, columna_destino, campo);
			draw_selector_cuadrado(fila_destino, columna_destino, campo);
			draw_cuadrado(fila_origen, columna_origen, campo);
			re_draw(campo);
			clic = 0;
		}

		if(mouse_b & 1) {
			fila = (mouse_y - 11) / 80;
			columna = (mouse_x - 11) / 80;
			if(hay_pieza(fila, columna, campo)) {
				draw_selector_cuadrado(fila, columna, campo);
			}
				pieza = obtener_pieza(fila, columna, campo);

			if(pieza != '_')
				clic += 1;
		}

		if(mouse_b & 2) {
			re_draw(campo);
			clic = 0;
		}

		if(keypressed()) tecla = readkey() >> 8;
	}

}

