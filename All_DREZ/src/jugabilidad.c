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

int f_rey_b = 7, c_rey_b = 4, f_rey_n = 0, c_rey_n = 4,
	f_origen_anterior = -1, c_origen_anterior = -1, f_destino_anterior = -1, c_destino_anterior = -1;

bool movi_torre_izq_b = false, movi_torre_der_b = false, movi_torre_izq_n = false, movi_torre_der_n = false, movi_rey_b = false,
	 movi_rey_n = false;


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
				case 'r': es_jaque = movimiento_permitido_rey(i, j, f_rey_n, c_rey_n, campo);
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
					case 'R': es_jaque = movimiento_permitido_rey(i, j, f_rey_b, c_rey_b, campo);
					break;
				}
			}
			if(es_jaque) break;
		}
		if(es_jaque) break;
	}
	return es_jaque;
}

bool condicion_enroque_izq_blanco(char campo[LADO][LADO]) {
	return !movi_torre_izq_b && !movi_rey_b && campo[7][1] == ' ' && campo[7][2] == ' ' && campo[7][3] == ' ';
}

bool condicion_enroque_der_blanco(char campo[LADO][LADO]) {
	return !movi_torre_der_b && !movi_rey_b && campo[7][5] == ' ' && campo[7][6] == ' ';
}

bool condicion_enroque_izq_negro(char campo[LADO][LADO]) {
	return !movi_torre_izq_n && !movi_rey_n && campo[0][1] == ' ' && campo[0][2] == ' ' && campo[0][3] == ' ';
}

bool condicion_enroque_der_negro(char campo[LADO][LADO]) {
	return !movi_torre_der_n && !movi_rey_n && campo[0][5] == ' ' && campo[0][6] == ' ';
}

void hacer_enroque_izq_blanco(char campo[LADO][LADO]) {
	campo[7][0] = ' ';
	campo[7][3] = 't';
}

void hacer_enroque_der_blanco(char campo[LADO][LADO]) {
	campo[7][7] = ' ';
	campo[7][5] = 't';
}

void hacer_enroque_izq_negro(char campo[LADO][LADO]) {
	campo[0][0] = ' ';
	campo[0][3] = 'T';
}

void hacer_enroque_der_negro(char campo[LADO][LADO]) {
	campo[0][7] = ' ';
	campo[0][5] = 'T';
}

void aplicar_movimiento(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(fila_origen == 0 && columna_origen == 0) {
		movi_torre_izq_n = true;
	}
	if(fila_origen == 0 && columna_origen == 7) {
		movi_torre_der_n = true;
	}
	if(fila_origen == 7 && columna_origen == 0) {
		movi_torre_izq_b = true;
	}
	if(fila_origen == 7 && columna_origen == 7) {
		movi_torre_der_b = true;
	}

	char pieza_origen = campo[fila_origen][columna_origen];

	if(condicion_enroque_der_blanco(campo) && pieza_origen == 'r' && fila_destino == 7 && columna_destino == 6) {
		hacer_enroque_der_blanco(campo);
		movi_rey_b = true;
		movi_torre_der_b = true;
	}
	if(condicion_enroque_izq_blanco(campo) && pieza_origen == 'r' && fila_destino == 7 && columna_destino == 2) {
		hacer_enroque_izq_blanco(campo);
		movi_rey_b = true;
		movi_torre_izq_b = true;
	}
	if(condicion_enroque_der_negro(campo) && pieza_origen == 'R' && fila_destino == 0 && columna_destino == 6) {
		hacer_enroque_der_negro(campo);
		movi_rey_n = true;
		movi_torre_der_n = true;
	}
	if(condicion_enroque_izq_negro(campo) && pieza_origen == 'R' && fila_destino == 0 && columna_destino == 2) {
		hacer_enroque_izq_negro(campo);
		movi_rey_n = true;
		movi_torre_izq_n = true;
	}

	if(fila_origen == 7 && columna_origen == 4) {
		movi_rey_b = true;
	}
	if(fila_origen == 0 && columna_origen == 4) {
		movi_rey_n = true;
	}

	campo[fila_destino][columna_destino] = pieza_origen;
	campo[fila_origen][columna_origen] = ' ';
}


bool movimiento_enroque_izq_blanco(int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
	return fila_origen == 7 && columna_origen == 4 && fila_destino == 7 && columna_destino == 2;
}

bool movimiento_enroque_der_blanco(int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
	return fila_origen == 7 && columna_origen == 4 && fila_destino == 7 && columna_destino == 6;
}

bool movimiento_enroque_izq_negro(int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
	return fila_origen == 0 && columna_origen == 4 && fila_destino == 0 && columna_destino == 2;
}

bool movimiento_enroque_der_negro(int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
	return fila_origen == 0 && columna_origen == 4 && fila_destino == 0 && columna_destino == 6;
}



bool mover_pieza_a_destino(int fila_origen, int fila_destino, int columna_origen, int columna_destino, char campo[LADO][LADO], bool *pieza_esta_en_hacke) {
	bool mover = false, enroque_der_blanca = false, enroque_izq_blanca = false, enroque_der_negra = false, enroque_izq_negra = false;

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
				enroque_der_blanca = movimiento_enroque_der_blanco(fila_origen, columna_origen, fila_destino, columna_destino);
				enroque_izq_blanca = movimiento_enroque_izq_blanco(fila_origen, columna_origen, fila_destino, columna_destino);

				if(enroque_der_blanca) {
					mover = condicion_enroque_der_blanco(campo);
				}
				if(enroque_izq_blanca) {
					mover = condicion_enroque_izq_blanco(campo);
				}
				if(!enroque_der_blanca && !enroque_izq_blanca) {
					mover = movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo);
				}
			break;
			case 'R':
				enroque_der_negra = movimiento_enroque_der_negro(fila_origen, columna_origen, fila_destino, columna_destino);
				enroque_izq_negra = movimiento_enroque_izq_negro(fila_origen, columna_origen, fila_destino, columna_destino);

				if(enroque_der_negra) {
					mover = condicion_enroque_der_negro(campo);
				}
				if(enroque_izq_negra) {
					mover = condicion_enroque_izq_negro(campo);
				}
				if(!enroque_der_negra && !enroque_izq_negra) {
					mover = movimiento_permitido_rey(fila_origen, columna_origen, fila_destino, columna_destino, campo);
				}
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

void seleccionar_pieza_negra_a_mover(BITMAP * pantalla, char pieza, char campo[LADO][LADO]) {
	switch(pieza) {
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

void seleccionar_pieza_blanca_a_mover(BITMAP * pantalla, char pieza, char campo[LADO][LADO]) {
	switch(pieza) {
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

void seleccionar_origen_blanca(BITMAP *pantalla, bool condicion_blanca_seleccionar, bool blanca_en_jaque, int fila, int columna, char *pieza, bool turno_blanca, int *clic_blanca, int *clic_negra, int *fila_origen, int *columna_origen, char campo[LADO][LADO]) {
	if(condicion_blanca_seleccionar && !blanca_en_jaque) {
		seleccionar_origen(pantalla, fila, columna, turno_blanca, clic_blanca, clic_negra, fila_origen, columna_origen, campo);
		*pieza = campo[*fila_origen][*columna_origen];
		campo[*fila_origen][*columna_origen] = ' ';
	}
	if(condicion_blanca_seleccionar && blanca_en_jaque) {
		seleccionar_origen(pantalla, fila, columna, turno_blanca, clic_blanca, clic_negra, fila_origen, columna_origen, campo);
		*pieza = campo[*fila_origen][*columna_origen];
		campo[*fila_origen][*columna_origen] = ' ';
	}
}

void seleccionar_origen_negra(BITMAP *pantalla, bool condicion_negra_seleccionar, bool negra_en_jaque, int fila, int columna, char *pieza, bool turno_blanca, int *clic_blanca, int *clic_negra, int *fila_origen, int *columna_origen, char campo[LADO][LADO]) {
	if(condicion_negra_seleccionar && !negra_en_jaque) {
		seleccionar_origen(pantalla, fila, columna, turno_blanca, clic_blanca, clic_negra, fila_origen, columna_origen, campo);
		*pieza = campo[*fila_origen][*columna_origen];
		campo[*fila_origen][*columna_origen] = ' ';
	}
	if(condicion_negra_seleccionar && negra_en_jaque) {
		seleccionar_origen(pantalla, fila, columna, turno_blanca, clic_blanca, clic_negra, fila_origen, columna_origen, campo);
		*pieza = campo[*fila_origen][*columna_origen];
		campo[*fila_origen][*columna_origen] = ' ';
	}
}

void dibujar_cuadros_seleccion_anterior(BITMAP *pantalla, char campo[LADO][LADO]) {
	if(f_origen_anterior != -1 && c_origen_anterior != -1 && f_destino_anterior != -1 && c_destino_anterior != -1) {
		draw_cuadrado(f_origen_anterior, c_origen_anterior, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
		draw_cuadrado(f_destino_anterior, c_destino_anterior, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
	}
}

void asignacion_variables_auxiliares(bool *turno_blanca, bool valor_turno_blanca, bool * mensaje_jaque, bool * mensaje_jaque_mate, int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
	*turno_blanca = valor_turno_blanca;
	*mensaje_jaque = true;
	*mensaje_jaque_mate = true;
	f_origen_anterior = fila_origen;
	c_origen_anterior = columna_origen;
	f_destino_anterior = fila_destino;
	c_destino_anterior = columna_destino;
}

bool es_fuera_de_menu(int *arr, int mouse_x, int mouse_y) {
	return !(mouse_x > arr[4] && mouse_x < arr[6] && mouse_y > arr[5] && mouse_y < arr[7]);
}


void seleccionar(char campo[LADO][LADO], SAMPLE * sonido_mover, BITMAP * pantalla) {
	int fila = 0, columna = 0, fila_origen = 0, fila_destino = -1, columna_origen = 0, columna_destino = -1,
		clic_blanca = 0, clic_negra = 0, arr[8] = {0};
	bool turno_blanca = true, blanca_en_jaque = false, negra_en_jaque = false, condicion_blanca_seleccionar = false,
		 condicion_negra_seleccionar = false, movio_blanca = false, movio_negra = false, jaque_mate = false,
		 mensaje_jaque = true, mensaje_jaque_mate = true, presione_clic_derecho = false, presione_clic_izquierdo = false;
	char pieza = ' ';

	LOCK_FUNCTION(close_button_handler);
	set_close_button_callback(close_button_handler);

	while(!close_button_pressed) {
		blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
		verificar_estado_de_rey(&mensaje_jaque_mate, &mensaje_jaque, &jaque_mate, negra_en_jaque, blanca_en_jaque, campo);
		rest(50);
		if(!jaque_mate && (mouse_b & 1)) {

			obtener_fila_y_columna(&fila, &columna);

			if(turno_blanca) {
				condicion_blanca_seleccionar = hay_pieza(fila, columna, campo) && es_pieza_blanca(campo[fila][columna]);
				seleccionar_origen_blanca(pantalla, condicion_blanca_seleccionar, blanca_en_jaque, fila, columna, &pieza, turno_blanca, &clic_blanca, &clic_negra, &fila_origen, &columna_origen, campo);

				if(clic_blanca > 0) {
					while(mouse_b & 1) {
						obtener_fila_y_columna(&fila_destino, &columna_destino);
						seleccionar_pieza_blanca_a_mover(pantalla, pieza, campo);
						re_draw(pantalla, campo);
						clic_blanca += 1;
						draw_cuadrado(fila_origen, columna_origen, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
						draw_cuadrado(fila_destino, columna_destino, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
						dibujar_cuadros_seleccion_anterior(pantalla, campo);
						presione_clic_izquierdo = true;
					}
					campo[fila_origen][columna_origen] = pieza;
				}

				if(fila_destino != -1 && columna_destino != -1) {
					movio_blanca = mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, &blanca_en_jaque);
					if(movio_blanca) {
						play_sample(sonido_mover, 200, 150, 1000, 0);
						aplicar_movimiento(fila_origen, columna_origen, fila_destino, columna_destino, campo);
						if(campo[fila_destino][columna_destino] == 'r') {
							f_rey_b = fila_destino;
							c_rey_b = columna_destino;
						}
						re_dibujar(pantalla, fila_origen, columna_origen, fila_destino, columna_destino, campo, movio_blanca);

						asignacion_variables_auxiliares(&turno_blanca, false, &mensaje_jaque, &mensaje_jaque_mate, fila_origen, columna_origen, fila_destino, columna_destino);
					} else {
						turno_blanca = true;
						draw_cuadrado(fila_origen, columna_origen, campo, ROJO, NEGRO, true, pantalla);
						draw_cuadrado(fila_destino, columna_destino, campo, ROJO, NEGRO,true, pantalla);
					}
					if(movio_blanca && verificar_jaque(pieza, fila_destino, columna_destino, campo)) {
						negra_en_jaque = true;
					}
					clic_blanca = 0;
				}

			} else {

				condicion_negra_seleccionar = hay_pieza(fila, columna, campo) && !es_pieza_blanca(campo[fila][columna]);
				seleccionar_origen_negra(pantalla, condicion_negra_seleccionar, negra_en_jaque, fila, columna, &pieza, turno_blanca, &clic_blanca, &clic_negra, &fila_origen, &columna_origen, campo);

				if(clic_negra > 0) {
					while(mouse_b & 1) {
						obtener_fila_y_columna(&fila_destino, &columna_destino);
						seleccionar_pieza_negra_a_mover(pantalla, pieza, campo);
						re_draw(pantalla, campo);
						clic_negra += 1;
						draw_cuadrado(fila_origen, columna_origen, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
						draw_cuadrado(fila_destino, columna_destino, campo, ROJO_SELECCION, NEGRO_SELECCION, true, pantalla);
						dibujar_cuadros_seleccion_anterior(pantalla, campo);
						presione_clic_izquierdo = true;
					}
					campo[fila_origen][columna_origen] = pieza;
				}

				if(fila_destino != -1 && columna_destino != -1) {
					movio_negra = mover_pieza_a_destino(fila_origen, fila_destino, columna_origen, columna_destino, campo, &negra_en_jaque);
					if(movio_negra) {
						play_sample(sonido_mover, 200, 150, 1000, 0);
						aplicar_movimiento(fila_origen, columna_origen, fila_destino, columna_destino, campo);
						if(campo[fila_destino][columna_destino] == 'R') {
							f_rey_n = fila_destino;
							c_rey_n = columna_destino;
						}
						re_dibujar(pantalla, fila_origen, columna_origen, fila_destino, columna_destino, campo, movio_negra);
						asignacion_variables_auxiliares(&turno_blanca, true, &mensaje_jaque, &mensaje_jaque_mate, fila_origen, columna_origen, fila_destino, columna_destino);
					} else {
						turno_blanca = false;
						draw_cuadrado(fila_origen, columna_origen, campo, ROJO, NEGRO, true, pantalla);
						draw_cuadrado(fila_destino, columna_destino, campo, ROJO, NEGRO, true, pantalla);
					}

					if(movio_negra && verificar_jaque(pieza, fila_destino, columna_destino, campo)) {
						blanca_en_jaque = true;
					}
					clic_negra = 0;
				}
			}
		}

		if(!presione_clic_derecho) {
			dibujar_cuadros_seleccion_anterior(pantalla, campo);
		}

		///////////////

		if(mouse_b & 1) {
			presione_clic_izquierdo = true;
		}

		if(mouse_b & 2) {
			re_draw(pantalla, campo);
			dibujar_cuadros_seleccion_anterior(pantalla, campo);

			if(mouse_x > 480) {
				menu(pantalla, mouse_y, mouse_x - 165, arr);
			} else {
				menu(pantalla, mouse_y, mouse_x, arr);
			}

			presione_clic_derecho = true;
		}

		if(presione_clic_derecho) {
			if(mouse_x > arr[0] && mouse_x < arr[2] && mouse_y > arr[1] && mouse_y < arr[3]) {
				menu_seleccion_promocion(pantalla, arr[0], arr[1] - 28, true);
			}
			else {
				menu_seleccion_promocion(pantalla, arr[0], arr[1] - 28, false);
			}
		}

		if(presione_clic_izquierdo && presione_clic_derecho && es_fuera_de_menu(arr, mouse_x, mouse_y)) {
			re_draw(pantalla, campo);
			presione_clic_derecho = false;
			presione_clic_izquierdo = false;
		}

		presione_clic_izquierdo = false;


		////////////
	}
}

