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

bool mover_pieza_a_destino(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO], SAMPLE * sonido_mover, bool *pieza_esta_en_hacke, char *pieza) {
	bool mover = false;

	if(campo[fila_origen][columna_origen] != ' ' && columna_destino != 8 && fila_destino != 8 && columna_origen != 8 && fila_origen != 8) {
		switch(campo[fila_origen][columna_origen]) {
			case 'p': if(movimiento_permitido_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'p';
			}
			break;
			case 'P': if(movimiento_permitido_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'P';
			}
			break;
			case 'T':if(movimiento_permitido_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'T';
			}
			break;
			case 't': if(movimiento_permitido_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 't';
			}
			break;
			case 'r': if(movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'r';
			}
			break;
			case 'R': if(movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'R';
			}
			break;
			case 'a':if(movimiento_permitido_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'a';
			}
			break;
			case 'A': if(movimiento_permitido_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'A';
			}
			break;
			case 'w':if(movimiento_permitido_reina(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'w';
			}
			break;
			case 'W': if(movimiento_permitido_reina(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'W';
			}
			break;
			case 'c':if(movimiento_permitido_caballo(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'c';
			}
			break;
			case 'C': if(movimiento_permitido_caballo(fila_origen, columna_origen, fila_destino, columna_destino, campo)) {
				mover = true;
				*pieza = 'C';
			}
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

bool verificar_hacke(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {

	bool es_jaque = es_jaque_rey(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_alfil(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_peon(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_torre(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_caballo(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_reina(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo);
	if(es_jaque) allegro_message("          jaque          ");

	return es_jaque;
}


volatile int close_button_pressed = FALSE;

void close_button_handler(void) {
	close_button_pressed = TRUE;
}

void seleccionar(char campo[LADO][LADO], SAMPLE * sonido_mover) {
	int fila = 0, columna = 0, fila_origen = 0, fila_destino = 0, columna_origen = 0, columna_destino = 0,
		clic_blanca = 0, clic_negra = 0 ,f_rey_b = 7, c_rey_b = 4, f_rey_n = 0, c_rey_n = 4;

	bool turno_blanca = true, blanca_esta_en_jaque = false, negra_esta_en_jaque = false;

	char pieza = ' ';

	LOCK_FUNCTION(close_button_handler);
	set_close_button_callback(close_button_handler);

	while(!close_button_pressed) {
		rest(75);

		if(mouse_b & 1) {
			fila = (mouse_y - 11) / 80;
			columna = (mouse_x - 11) / 80;

			if(turno_blanca) {
				if(hay_pieza(fila, columna, campo) && es_pieza_blanca(fila, columna, campo) && !blanca_esta_en_jaque) {
					draw_selector_cuadrado(fila, columna, campo);
					if(clic_blanca == 0) {
						fila_origen = fila;
						columna_origen = columna;
						clic_blanca = 1;
					}
				} else if(hay_pieza(fila, columna, campo) && es_pieza_blanca(fila, columna, campo) && blanca_esta_en_jaque) {
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
					if(mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, sonido_mover, &blanca_esta_en_jaque, &pieza)) {
						if(campo[fila_destino][columna_destino] == 'r') {
							f_rey_b = fila_destino;
							c_rey_b = columna_destino;
						}
						turno_blanca = false;
					} else {
						turno_blanca = true;
					}
					draw_selector_cuadrado(fila_destino, columna_destino, campo);
					draw_cuadrado(fila_origen, columna_origen, campo);
					re_draw(campo);
					if(verificar_hacke(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) {
						negra_esta_en_jaque = true;
					}
					clic_blanca = 0;
				}

			} else {
				if(hay_pieza(fila, columna, campo) && !es_pieza_blanca(fila, columna, campo) && !negra_esta_en_jaque) {
					draw_selector_cuadrado(fila, columna, campo);
					if(clic_negra == 0) {
						fila_origen = fila;
						columna_origen = columna;
						clic_negra = 1;
					}
				} else if(hay_pieza(fila, columna, campo) && !es_pieza_blanca(fila, columna, campo) && negra_esta_en_jaque) {
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
					if(mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, sonido_mover, &negra_esta_en_jaque, &pieza)) {
						if(campo[fila_destino][columna_destino] == 'R') {
							f_rey_n = fila_destino;
							c_rey_n = columna_destino;
						}
						turno_blanca = true;
					} else {
						turno_blanca = false;
					}
					draw_selector_cuadrado(fila_destino, columna_destino, campo);
					draw_cuadrado(fila_origen, columna_origen, campo);
					re_draw(campo);
					if(verificar_hacke(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) {
						blanca_esta_en_jaque = true;
					}
					clic_negra = 0;
				}

			}

		}

		if(mouse_b & 2) {
			re_draw(campo);
			if(turno_blanca) clic_blanca = 0; else clic_negra = 0;
		}
	}

}

