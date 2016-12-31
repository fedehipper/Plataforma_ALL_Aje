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
#define ROJO 4
#define NEGRO 16
#define ROJO_SELECCION 12
#define NEGRO_SELECCION 24

int f_rey_b = 7, c_rey_b = 4, f_rey_n = 0, c_rey_n = 4;


bool es_pieza_blanca(char pieza) {
	return pieza == 'w' || pieza == 'a' || pieza == 'r' || pieza == 't' || pieza == 'c' || pieza == 'p';
}

bool verificar_jaque_intermedio_blancas(char campo[LADO][LADO]) {
	int i,j;
	bool es_jaque = false;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] != ' ' && es_pieza_blanca(campo[i][j])) {
				switch(campo[i][j]) {
				case 'a': es_jaque = movimiento_permitido_alfil(i, j, f_rey_n , c_rey_n, campo);
				break;
				case 'p': es_jaque = movimiento_permitido_peon(i, j, f_rey_n, c_rey_n, campo);
				break;
				case 'c': es_jaque = movimiento_permitido_caballo(i, j, f_rey_n, c_rey_n, campo);
				break;
				case 'w': es_jaque = movimiento_permitido_reina(i, j, f_rey_n, c_rey_n, campo);
				break;
				case 't': es_jaque = movimiento_permitido_torre(i, j, f_rey_n, c_rey_n, campo);
				break;
				}
			}
			if(es_jaque) break;
		}
		if(es_jaque) break;
	}
	return es_jaque;
}


bool verificar_jaque_intermedio_negras(char campo[LADO][LADO]) {
	int i,j;
	bool es_jaque = false;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] != ' ' && !es_pieza_blanca(campo[i][j])) {
				switch(campo[i][j]) {
					case 'A': es_jaque = movimiento_permitido_alfil(i, j, f_rey_b , c_rey_b, campo);
					break;
					case 'P': es_jaque = movimiento_permitido_peon(i, j, f_rey_b , c_rey_b, campo);
					break;
					case 'C': es_jaque = movimiento_permitido_caballo(i, j, f_rey_b , c_rey_b, campo);
					break;
					case 'W': es_jaque = movimiento_permitido_reina(i, j, f_rey_b , c_rey_b, campo);
					break;
					case 'T': es_jaque = movimiento_permitido_torre(i, j, f_rey_b , c_rey_b, campo);
					break;
				}
			}
			if(es_jaque) break;
		}
		if(es_jaque) break;
	}
	return es_jaque;
}

void aplicar_movimiento(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	campo[fila_destino][columna_destino] = campo[fila_origen][columna_origen];
	campo[fila_origen][columna_origen] = ' ';
}

bool mover_pieza_a_destino(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO], bool *pieza_esta_en_hacke) {
	bool mover = false;

	if(campo[fila_origen][columna_origen] != ' ' && columna_destino != 8 && fila_destino != 8 && columna_origen != 8 && fila_origen != 8) {
		switch(campo[fila_origen][columna_origen]) {
			case 'p':
			case 'P': if(movimiento_permitido_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo))
				mover = !si_se_mueve_es_jaque_peon(fila_origen, columna_origen, fila_destino, columna_destino, campo, f_rey_b, c_rey_b, f_rey_n, c_rey_n);
			break;
			case 'T':
			case 't': if(movimiento_permitido_torre(fila_origen, columna_origen, fila_destino, columna_destino, campo))
				mover = !si_se_mueve_es_jaque_torre(fila_origen, columna_origen, fila_destino, columna_destino,  campo, f_rey_b, c_rey_b, f_rey_n, c_rey_n);
			break;
			case 'r':
			case 'R': if(movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo)) mover = true;
			break;
			case 'a':
			case 'A': if(movimiento_permitido_alfil(fila_origen, columna_origen, fila_destino, columna_destino, campo))
				mover = !si_se_mueve_es_jaque_alfil(fila_origen, columna_origen, fila_destino, columna_destino,  campo, f_rey_b, c_rey_b, f_rey_n, c_rey_n);
			break;
			case 'w':
			case 'W': if(movimiento_permitido_reina(fila_origen, columna_origen, fila_destino, columna_destino, campo))
				mover = !si_se_mueve_es_jaque_reina(fila_origen, columna_origen, fila_destino, columna_destino,  campo, f_rey_b, c_rey_b, f_rey_n, c_rey_n);
			break;
			case 'c':
			case 'C': if(movimiento_permitido_caballo(fila_origen, columna_origen, fila_destino, columna_destino, campo))
				mover = !si_se_mueve_es_jaque_caballo(fila_origen, columna_origen, fila_destino, columna_destino,  campo, f_rey_b, c_rey_b, f_rey_n, c_rey_n);
			break;
		}
		if(mover && *pieza_esta_en_hacke) *pieza_esta_en_hacke = false;
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


bool verificar_jaque(char pieza, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	bool es_jaque = es_jaque_rey(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_alfil(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_peon(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_torre(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_caballo(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo) ||
					es_jaque_reina(pieza, fila_destino, columna_destino, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo);
	return es_jaque;
}


volatile int close_button_pressed = FALSE;

void close_button_handler(void) {
	close_button_pressed = TRUE;
}

void seleccionar_origen(BITMAP *pantalla, int fila, int columna, bool turno_blanca, int *clic_blanca, int *clic_negra, int *fila_origen, int *columna_origen, char campo[LADO][LADO]) {
	draw_cuadrado(fila, columna, campo, ROJO_SELECCION, NEGRO_SELECCION, false, pantalla);
	if(turno_blanca) {
		if(*clic_blanca == 0) {
			*fila_origen = fila;
			*columna_origen = columna;
			*clic_blanca = 1;
		}
	} else {
		if(*clic_negra == 0) {
			*fila_origen = fila;
			*columna_origen = columna;
			*clic_negra = 1;
		}
	}
}

void re_dibujar(BITMAP *pantalla, int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO], bool se_movio) {
	draw_cuadrado(fila_origen, columna_origen, campo, ROJO, NEGRO, true, pantalla);
	re_draw(pantalla, campo);
	if(se_movio) {
		draw_cuadrado(fila_origen, columna_origen, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
		draw_cuadrado(fila_destino, columna_destino, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
	}
}

bool no_hay_movimiento_permitido_blancas(char campo[LADO][LADO]) {
	int i, j, k, l;
	bool aux = false;
	bool se_puede_mover = false;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] != ' ' && !es_pieza_blanca(campo[i][j])) {
				for(k = 0 ; k < LADO ; k++) {
					for(l = 0 ; l < LADO ; l++) {
						se_puede_mover = mover_pieza_a_destino(i, k, j, l, campo, &aux);
						if(se_puede_mover) break;
					}
					if(se_puede_mover) break;
				}
				if(se_puede_mover) break;
			}
			if(se_puede_mover) break;
		}
		if(se_puede_mover) break;
	}
	return !se_puede_mover;
}


bool no_hay_movimiento_permitido_negras(char campo[LADO][LADO]) {
	int i, j, k, l;
	bool aux = false;
	bool se_puede_mover = false;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] != ' ' && es_pieza_blanca(campo[i][j])) {
				for(k = 0 ; k < LADO ; k++) {
					for(l = 0 ; l < LADO ; l++) {
						se_puede_mover = mover_pieza_a_destino(i, k, j, l, campo, &aux);
						if(se_puede_mover) break;
					}
					if(se_puede_mover) break;
				}
				if(se_puede_mover) break;
			}
			if(se_puede_mover) break;
		}
		if(se_puede_mover) break;
	}
	return !se_puede_mover;
}

void obtener_fila_y_columna(int * fila, int * columna) {
	*fila = (mouse_y - 11) / 80;
	*columna = (mouse_x - 11) / 80;
}

void verificar_estado_de_rey(bool * mensaje_jaque_mate, bool * mensaje_jaque, bool * jaque_mate, bool negra_esta_en_jaque, bool blanca_esta_en_jaque, char campo[LADO][LADO]) {
	if(*mensaje_jaque_mate && (no_hay_movimiento_permitido_negras(campo) || no_hay_movimiento_permitido_blancas(campo)) && (negra_esta_en_jaque || blanca_esta_en_jaque)) {
		*jaque_mate = true;
		allegro_message("\n          JAQUE MATE          \n\n");
		*mensaje_jaque_mate = false;
	}

	if(*mensaje_jaque_mate && (no_hay_movimiento_permitido_negras(campo) || no_hay_movimiento_permitido_blancas(campo)) && !negra_esta_en_jaque && !blanca_esta_en_jaque) {
		*jaque_mate = true;
		allegro_message("\n          EMPATE POR AHOGADO          \n\n");
		*mensaje_jaque_mate = false;
	}


	if(*mensaje_jaque && (verificar_jaque_intermedio_negras(campo) || verificar_jaque_intermedio_blancas(campo)) && !(no_hay_movimiento_permitido_negras(campo) || no_hay_movimiento_permitido_blancas(campo))) {
		allegro_message("\n          JAQUE          \n\n");
		*mensaje_jaque = false;
	}
}

void seleccionar_pieza_negra_a_mover(BITMAP * pantalla, int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	switch(campo[fila_origen][columna_origen]) {
		case 'P': dibujar_peon_en_movimiento(pantalla,'P', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'A': dibujar_alfil_en_movimiento(pantalla,'A', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'T': dibujar_torre_en_movimiento(pantalla,'T', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'W': dibujar_reina_en_movimiento(pantalla,'W', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'R': dibujar_rey_en_movimiento(pantalla,'R', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'C': dibujar_caballo_en_movimiento(pantalla,'C', mouse_x - 40 , mouse_y - 40, campo);
		break;
	}
}

void seleccionar_pieza_blanca_a_mover(BITMAP * pantalla, int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	switch(campo[fila_origen][columna_origen]) {
		case 'p': dibujar_peon_en_movimiento(pantalla, 'p', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'a': dibujar_alfil_en_movimiento(pantalla,'a', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 't': dibujar_torre_en_movimiento(pantalla,'t', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'w': dibujar_reina_en_movimiento(pantalla,'w', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'r': dibujar_rey_en_movimiento(pantalla,'r', mouse_x - 40 , mouse_y - 40, campo);
		break;
		case 'c': dibujar_caballo_en_movimiento(pantalla,'c', mouse_x - 40 , mouse_y - 40, campo);
		break;
	}
}



void seleccionar(char campo[LADO][LADO], SAMPLE * sonido_mover, BITMAP * pantalla) {
	int fila = 0, columna = 0, fila_origen = 0, fila_destino = 0, columna_origen = 0, columna_destino = 0,
		clic_blanca = 0, clic_negra = 0;
	bool turno_blanca = true, blanca_esta_en_jaque = false, negra_esta_en_jaque = false, condicion_blanca_seleccionar = false,
		 condicion_negra_seleccionar = false, movio_blanca = false, movio_negra = false, jaque_mate = false,
		 mensaje_jaque = true, mensaje_jaque_mate = true;
	char pieza = ' ';

	LOCK_FUNCTION(close_button_handler);
	set_close_button_callback(close_button_handler);

	while(!close_button_pressed) {

		if(!jaque_mate && (mouse_b & 1)) {

			obtener_fila_y_columna(&fila, &columna);

			if(turno_blanca) {
				condicion_blanca_seleccionar = hay_pieza(fila, columna, campo) && es_pieza_blanca(campo[fila][columna]);

				if(condicion_blanca_seleccionar && !blanca_esta_en_jaque) {
					seleccionar_origen(pantalla, fila, columna, turno_blanca, &clic_blanca, &clic_negra, &fila_origen, &columna_origen, campo);
				}
				if(condicion_blanca_seleccionar && blanca_esta_en_jaque) {
					seleccionar_origen(pantalla, fila, columna, turno_blanca, &clic_blanca, &clic_negra, &fila_origen, &columna_origen, campo);
				}

				if(clic_blanca > 0) {
					while((mouse_b & 1)) {
						obtener_fila_y_columna(&fila_destino, &columna_destino);
						seleccionar_pieza_blanca_a_mover(pantalla, fila_origen, columna_origen, campo);
						//rest(65);
						re_draw(pantalla, campo);
						clic_blanca += 1;
					}
				}

				if(fila_destino != 0 || columna_destino != 0) {
					pieza = campo[fila_origen][columna_origen];
					movio_blanca = mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, &blanca_esta_en_jaque);
					if(movio_blanca) {
						play_sample(sonido_mover, 200, 150, 1000, 0);
						aplicar_movimiento(fila_origen, columna_origen, fila_destino, columna_destino, campo);
						if(campo[fila_destino][columna_destino] == 'r') {
							f_rey_b = fila_destino;
							c_rey_b = columna_destino;
						}
						turno_blanca = false;
						re_dibujar(pantalla, fila_origen, columna_origen, fila_destino, columna_destino, campo, movio_blanca);
						verificar_jaque_intermedio_blancas(campo);
						mensaje_jaque = true;
						mensaje_jaque_mate = true;
					} else {
						turno_blanca = true;
						draw_cuadrado(fila_origen, columna_origen, campo, ROJO, NEGRO, true, pantalla);
						draw_cuadrado(fila_destino, columna_destino, campo, ROJO, NEGRO,true, pantalla);
					}
					if(movio_blanca && verificar_jaque(pieza, fila_destino, columna_destino, campo)) {
						negra_esta_en_jaque = true;
					}
					clic_blanca = 0;
				}

			} else {

				condicion_negra_seleccionar = hay_pieza(fila, columna, campo) && !es_pieza_blanca(campo[fila][columna]);

				if(condicion_negra_seleccionar && !negra_esta_en_jaque) {
					seleccionar_origen(pantalla, fila, columna, turno_blanca, &clic_blanca, &clic_negra, &fila_origen, &columna_origen, campo);
				}
				if(condicion_negra_seleccionar && negra_esta_en_jaque) {
					seleccionar_origen(pantalla, fila, columna, turno_blanca, &clic_blanca, &clic_negra, &fila_origen, &columna_origen, campo);
				}

				if(clic_negra > 0) {
					while((mouse_b & 1)) {
						obtener_fila_y_columna(&fila_destino, &columna_destino);
						seleccionar_pieza_negra_a_mover(pantalla,fila_origen, columna_origen, campo);
						//rest(65);
						re_draw(pantalla, campo);
						clic_negra += 1;
					}
				}

				if(fila_destino != 0 || columna_destino != 0) {
					pieza = campo[fila_origen][columna_origen];
					movio_negra = mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, &negra_esta_en_jaque);
					if(movio_negra) {
						play_sample(sonido_mover, 200, 150, 1000, 0);
						aplicar_movimiento(fila_origen, columna_origen, fila_destino, columna_destino, campo);
						if(campo[fila_destino][columna_destino] == 'R') {
							f_rey_n = fila_destino;
							c_rey_n = columna_destino;
						}
						turno_blanca = true;
						re_dibujar(pantalla, fila_origen, columna_origen, fila_destino, columna_destino, campo, movio_negra);
						mensaje_jaque = true;
						mensaje_jaque_mate = true;
					} else {
						turno_blanca = false;
						draw_cuadrado(fila_origen, columna_origen, campo, ROJO, NEGRO, true, pantalla);
						draw_cuadrado(fila_destino, columna_destino, campo, ROJO, NEGRO, true, pantalla);
					}

					if(movio_negra && verificar_jaque(pieza, fila_destino, columna_destino, campo)) {
						blanca_esta_en_jaque = true;
					}
					clic_negra = 0;
				}
			}

		}
		verificar_estado_de_rey(&mensaje_jaque_mate, &mensaje_jaque, &jaque_mate, negra_esta_en_jaque, blanca_esta_en_jaque, campo);
	}

}

