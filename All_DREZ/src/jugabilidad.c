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

void aplicar_movimiento(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
	campo[fila_origen][columna_origen] = ' ';
}

bool mover_pieza_a_destino(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO], SAMPLE * sonido_mover, bool *pieza_esta_en_hacke) {
	bool mover = false;

	if(campo[fila_origen][columna_origen] != ' ' && columna_destino != 8 && fila_destino != 8 && columna_origen != 8 && fila_origen != 8) {
		switch(campo[fila_origen][columna_origen]) {
			case 'p':
			case 'P': if(movimiento_permitido_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
			case 'T':
			case 't': if(movimiento_permitido_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
			case 'r':
			case 'R': if(movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
			case 'a':
			case 'A': if(movimiento_permitido_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
			case 'w':
			case 'W': if(movimiento_permitido_reina(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
			case 'c':
			case 'C': if(movimiento_permitido_caballo(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
		}
		if(mover && !*pieza_esta_en_hacke) {
			aplicar_movimiento(fila_origen, columna_origen, fila_destino, columna_destino, campo);
			play_sample(sonido_mover, 200, 150, 1000, 0);
		}
		if(mover && *pieza_esta_en_hacke && (campo[fila_origen][columna_origen] == 'R' || campo[fila_origen][columna_origen] == 'r')) {
			aplicar_movimiento(fila_origen, columna_origen, fila_destino, columna_destino, campo);
			play_sample(sonido_mover, 200, 150, 1000, 0);
			*pieza_esta_en_hacke = false;
		}
	}
	return mover;
}

bool misma_coordenada(int fila, int columna, int nueva_fila, int nueva_columna) {
	return fila == nueva_fila && columna == nueva_columna;
}

char obtener_pieza(int fila, int columna, char campo[LADO][LADO]) {
	return (fila != 8 && columna != 8) ? campo[fila][columna] : ' ';
}

bool hay_pieza(int fila, int columna, char campo[LADO][LADO]) {
	return fila != 8 && columna != 8 && campo[fila][columna] != ' ';
}

bool es_pieza_blanca(int fila, int columna, char campo[LADO][LADO]) {
	char pieza = campo[fila][columna];
	return pieza == 'w' || pieza == 'a' || pieza == 'r' || pieza == 't' || pieza == 'c' || pieza == 'p';
}

bool verificar_hacke(int fila_origen, int columna_origen, char campo[LADO][LADO]) {

	bool es_hacke = es_hacke_rey(fila_origen, columna_origen, campo) ||
					es_hacke_alfil(fila_origen, columna_origen, campo) ||
					es_hacke_peon(fila_origen, columna_origen, campo) ||
					es_hacke_torre(fila_origen, columna_origen, campo) ||
					es_hacke_caballo(fila_origen, columna_origen, campo) ||
					es_hacke_reina(fila_origen, columna_origen, campo);
	if(es_hacke) allegro_message("hacke");
	return es_hacke;
}

void seleccionar(char campo[LADO][LADO], SAMPLE * sonido_mover) {
	int fila = 0, columna = 0, fila_origen = 0, fila_destino = 0, columna_origen = 0, columna_destino = 0,
		clic_blanca = 0, clic_negra = 0, tecla = 0;

	bool turno_blanca = true, *blanca_esta_en_hacke = false, *negra_esta_en_hacke = false;

	while(tecla != KEY_ESC) {
		rest(75);

		if(mouse_b & 1) {
			fila = (mouse_y - 11) / 80;
			columna = (mouse_x - 11) / 80;

			if(turno_blanca) {
				if(hay_pieza(fila, columna, campo) && es_pieza_blanca(fila, columna, campo) && !blanca_esta_en_hacke) {
					draw_selector_cuadrado(fila, columna, campo);
					if(clic_blanca == 0) {
						fila_origen = fila;
						columna_origen = columna;
						clic_blanca = 1;
					}
				} else if(hay_pieza(fila, columna, campo) && es_pieza_blanca(fila, columna, campo) && blanca_esta_en_hacke) {
					if(campo[fila][columna] == 'r') {
						draw_selector_cuadrado(fila, columna, campo);
						if(clic_blanca == 0) {
							fila_origen = fila;
							columna_origen = columna;
							clic_blanca = 1;
						}
					}
				}

				if(clic_blanca == 1 && (fila != fila_origen || columna != columna_origen)) {
					fila_destino = fila;
					columna_destino = columna;
					clic_blanca = 2;
				}

				if(clic_blanca == 2) {
					if(mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, sonido_mover, &blanca_esta_en_hacke)) {
						turno_blanca = false;
					} else {
						turno_blanca = true;
					}
					draw_selector_cuadrado(fila_destino, columna_destino, campo);
					draw_cuadrado(fila_origen, columna_origen, campo);
					re_draw(campo);
					if(verificar_hacke(fila_destino, columna_destino, campo)) negra_esta_en_hacke = true;
					clic_blanca = 0;
				}

			} else {
				if(hay_pieza(fila, columna, campo) && !es_pieza_blanca(fila, columna, campo) && !negra_esta_en_hacke) {
					draw_selector_cuadrado(fila, columna, campo);
					if(clic_negra == 0) {
						fila_origen = fila;
						columna_origen = columna;
						clic_negra = 1;
					}
				} else if(hay_pieza(fila, columna, campo) && !es_pieza_blanca(fila, columna, campo) && negra_esta_en_hacke) {
					if(campo[fila][columna] == 'R') {
						draw_selector_cuadrado(fila, columna, campo);
						if(clic_negra == 0) {
							fila_origen = fila;
							columna_origen = columna;
							clic_negra = 1;
						}
					}
				}

				if(clic_negra == 1 && (fila != fila_origen || columna != columna_origen)) {
					fila_destino = fila;
					columna_destino = columna;
					clic_negra = 2;
				}

				if(clic_negra == 2) {
					if(mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, sonido_mover, &negra_esta_en_hacke)) {
						turno_blanca = true;
					} else {
						turno_blanca = false;
					}
					draw_selector_cuadrado(fila_destino, columna_destino, campo);
					draw_cuadrado(fila_origen, columna_origen, campo);
					re_draw(campo);
					if(verificar_hacke(fila_destino, columna_destino, campo)) blanca_esta_en_hacke = true;
					clic_negra = 0;
				}

			}

		}

		if(mouse_b & 2) {
			re_draw(campo);
			if(turno_blanca) clic_blanca = 0; else clic_negra = 0;
		}

		if(keypressed()) tecla = readkey() >> 8;
	}

}

