#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "piezas.h"

#define LADO 8
#define LADO_PIEZA 71
#define RETARDO_MOVIMIENTO_PIEZA 10
#define GRIS 28
#define COLOR_TEXTO 16

BITMAP *b_peon_blanco, *b_peon_negro, *b_torre_blanca, *b_torre_negra, *b_alfil_blanco, *b_alfil_negro, *b_caballo_blanco,
	   *b_caballo_negro, *b_reina_blanca, *b_reina_negra, *b_rey_blanco, *b_rey_negro;

void draw_coordenadas(BITMAP * pantalla) {
	textprintf_justify_ex(pantalla, font, 45, 10, 655, 0, 114, 66, "A         B         C         D         E         F         G         H");
	textprintf_justify_ex(pantalla, font, 655, 10, 45, 0, 114, 66, "8");
	textprintf_justify_ex(pantalla, font, 655, 10, 125, 0, 114, 66, "7");
	textprintf_justify_ex(pantalla, font, 655, 10, 205, 0, 114, 66, "6");
	textprintf_justify_ex(pantalla, font, 655, 10, 285, 0, 114, 66, "5");
	textprintf_justify_ex(pantalla, font, 655, 10, 365, 0, 114, 66, "4");
	textprintf_justify_ex(pantalla, font, 655, 10, 445, 0, 114, 66, "3");
	textprintf_justify_ex(pantalla, font, 655, 10, 525, 0, 114, 66, "2");
	textprintf_justify_ex(pantalla, font, 655, 10, 605, 0, 114, 66, "1");
}

bool impar_relativo(int i, int j) {
	return fmod(i + j, 2)  > 0;
}

bool par_relativo(int i, int j) {
	return fmod(i + j, 2) == 0;
}

void draw_cuadros_tablero(BITMAP *pantalla) {
	int i, j;
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 8 ; j++) {
			if(impar_relativo(i, j))
				rectfill(pantalla, 11 + 80 * i, 11 + 80 * j, 90 + 80 * i, 90 + 80 * j, 114);
			else
				rectfill(pantalla, 11 + 80 * i, 11 + 80 * j, 90 + 80 * i, 90 + 80 * j, 66);
		}
	}
}

void tablero_en_blanco(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 8 ; j++) {
			campo[i][j] = ' ';
		}
	}
}

void inicializar_posicion_peones(char campo[LADO][LADO]) {
	int i;
	for(i = 0 ; i < 8 ; i++) {
		campo[1][i] = 'P';
		campo[6][i] = 'p';
	}
}

void inicializar_posicion_reinas(char campo[LADO][LADO]) {
	campo[0][3] = 'W';
	campo[7][3] = 'w';
}

void inicializar_posicion_reyes(char campo[LADO][LADO]) {
	campo[0][4] = 'R';
	campo[7][4] = 'r';
}

void inicializar_posicion_alfiles(char campo[LADO][LADO]) {
	campo[0][2] = 'A';
	campo[0][5] = 'A';
	campo[7][2] = 'a';
	campo[7][5] = 'a';
}

void inicializar_posicion_torres(char campo[LADO][LADO]) {
	campo[0][0] = 'T';
	campo[0][7] = 'T';
	campo[7][0] = 't';
	campo[7][7] = 't';
}

void inicializar_posicion_caballos(char campo[LADO][LADO]) {
	campo[0][1] = 'C';
	campo[0][6] = 'C';
	campo[7][1] = 'c';
	campo[7][6] = 'c';
}

void inicializar_posicion_piezas(char campo[LADO][LADO]) {
	inicializar_posicion_peones(campo);
	inicializar_posicion_torres(campo);
	inicializar_posicion_alfiles(campo);
	inicializar_posicion_caballos(campo);
	inicializar_posicion_reinas(campo);
	inicializar_posicion_reyes(campo);
}

void jugador_blanco(BITMAP * pantalla) {
	textout_centre_ex(pantalla, font, "JUGADOR BLANCO", 762, 345, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "PROMOCION", 765, 65, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "reina", 720, 85, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "torre", 720, 105, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "alfil", 810, 85, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "caballo", 819, 105, COLOR_TEXTO, GRIS);
	circlefill(pantalla, 685, 108, 7, GRIS - 3);
	circlefill(pantalla, 775, 108, 7, GRIS - 3);
	circlefill(pantalla, 685, 89, 7, GRIS - 3);
	circlefill(pantalla, 775, 89, 7, GRIS - 3);
	textout_centre_ex(pantalla, font, "CRONOMETRO", 765, 155, COLOR_TEXTO, GRIS);
}

void jugador_negro(BITMAP * pantalla) {
	textout_centre_ex(pantalla, font, "JUGADOR NEGRO", 760, 25, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "PROMOCION", 765, 385, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "reina", 720, 405, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "torre", 720, 425, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "alfil", 810, 405, COLOR_TEXTO, GRIS);
	textout_centre_ex(pantalla, font, "caballo", 819, 425, COLOR_TEXTO, GRIS);
	circlefill(pantalla, 685, 409, 7, GRIS - 3);
	circlefill(pantalla, 775, 409, 7, GRIS - 3);
	circlefill(pantalla, 685, 429, 7, GRIS - 3);
	circlefill(pantalla, 775, 429, 7, GRIS - 3);
	textout_centre_ex(pantalla, font, "CRONOMETRO", 765, 475, COLOR_TEXTO, GRIS);
}

// ya son las coordenadas posta
void seleccionar_promocion(BITMAP * pantalla, int mouse_x, int mouse_y, char *pieza_seleccionada, bool turno_blanca) {
	if(!turno_blanca) {
		if(mouse_x > 675 && mouse_x < 695 && mouse_y > 98 && mouse_y < 120) *pieza_seleccionada = 'T';
		if(mouse_x > 768 && mouse_x < 782 && mouse_y > 98 && mouse_y < 120) *pieza_seleccionada = 'C';
		if(mouse_x > 675 && mouse_x < 695 && mouse_y > 82 && mouse_y < 96) *pieza_seleccionada = 'W';
		if(mouse_x > 768 && mouse_x < 782 && mouse_y > 82 && mouse_y < 96) *pieza_seleccionada = 'A';
	} else {
		if(mouse_x > 675 && mouse_x < 695 && mouse_y > 402 && mouse_y < 416) *pieza_seleccionada = 'w';
		if(mouse_x > 768 && mouse_x < 782 && mouse_y > 402 && mouse_y < 416) *pieza_seleccionada = 'a';
		if(mouse_x > 675 && mouse_x < 695 && mouse_y > 422 && mouse_y < 436) *pieza_seleccionada = 't';
		if(mouse_x > 768 && mouse_x < 782 && mouse_y > 422 && mouse_y < 436) *pieza_seleccionada = 'c';
	}
}

void dibujar_seleccion_promocion(BITMAP *pantalla, char pieza_promocion_blanca, char pieza_promocion_negra) {
	switch(pieza_promocion_blanca) {
		case 'w': circlefill(pantalla, 685, 409, 7, 2); break;
		case 'a': circlefill(pantalla, 775, 409, 7, 2); break;
		case 't': circlefill(pantalla, 685, 429, 7, 2); break;
		case 'c': circlefill(pantalla, 775, 429, 7, 2); break;
	}
	switch(pieza_promocion_negra) {
		case 'W': circlefill(pantalla, 685, 89, 7, 2); break;
		case 'A': circlefill(pantalla, 775, 89, 7, 2); break;
		case 'T': circlefill(pantalla, 685, 108, 7, 2); break;
		case 'C': circlefill(pantalla, 775, 108, 7, 2); break;
	}
}

void draw_tablero(BITMAP *pantalla) {
	rectfill(pantalla, 0, 0, 664, 667, 66);
	rect(pantalla, 10, 10, 651, 651, 114);
	rectfill(pantalla, 665, 0, 870, 667, GRIS);
	line(pantalla, 665, 330, 870, 330, GRIS + 1);
	draw_coordenadas(pantalla);
	draw_cuadros_tablero(pantalla);
	jugador_blanco(pantalla);
	jugador_negro(pantalla);
}

void crear_reina_blanca(void) {
	int i, j;
	b_reina_blanca = create_bitmap(110, 110);
	clear_bitmap(b_reina_blanca);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_reina_blanca, i, j, palette_color[reina_blanca[j][i]]);
		}
	}
}

void crear_caballo_blanco(void) {
	int i, j;
	b_caballo_blanco = create_bitmap(110, 110);
	clear_bitmap(b_caballo_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_caballo_blanco, i, j, palette_color[caballo_blanco[j][i]]);
		}
	}
}

void crear_rey_blanco(void) {
	int i, j;
	b_rey_blanco = create_bitmap(110, 110);
	clear_bitmap(b_rey_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_rey_blanco, i, j, palette_color[rey_blanco[j][i]]);
		}
	}
}

void crear_rey_negro(void) {
	int i, j;
	b_rey_negro = create_bitmap(110, 110);
	clear_bitmap(b_rey_negro);
	for(i = 0 ; i < LADO_PIEZA; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_rey_negro, i, j, palette_color[rey_negro[j][i]]);
		}
	}
}

void crear_reina_negra(void) {
	int i, j;
	b_reina_negra = create_bitmap(110, 110);
	clear_bitmap(b_reina_negra);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_reina_negra, i, j, palette_color[reina_negra[j][i]]);
		}
	}
}

void crear_caballo_negro(void) {
	int i, j;
	b_caballo_negro = create_bitmap(110, 110);
	clear_bitmap(b_caballo_negro);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_caballo_negro, i, j, palette_color[caballo_negro[j][i]]);
		}
	}
}
void crear_torre_blanca(void) {
	int i, j;
	b_torre_blanca = create_bitmap(110, 110);
	clear_bitmap(b_torre_blanca);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_torre_blanca, i, j, palette_color[torre_blanca[j][i]]);
		}
	}
}

void crear_alfil_blanco(void) {
	int i, j;
	b_alfil_blanco = create_bitmap(115, 115);
	clear_bitmap(b_alfil_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_alfil_blanco, i, j, palette_color[alfil_blanco[j][i]]);
		}
	}
}

void crear_alfil_negro(void) {
	int i, j;
	b_alfil_negro = create_bitmap(115, 115);
	clear_bitmap(b_alfil_negro);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_alfil_negro, i, j, palette_color[alfil_negro[j][i]]);
		}
	}
}

void crear_torre_negra(void) {
	int i, j;
	b_torre_negra = create_bitmap(110, 110);
	clear_bitmap(b_torre_negra);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_torre_negra, i, j, palette_color[torre_negra[j][i]]);
		}
	}
}

void crear_peon_blanco(void) {
	int i, j;
	b_peon_blanco = create_bitmap(110, 110);
	clear(b_peon_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA  ; j++)
			putpixel(b_peon_blanco, i, j, palette_color[peon_blanco[j][i]]);
	}
}

void crear_peon_negro(void) {
	int i, j;
	b_peon_negro = create_bitmap(110, 110);
	clear_bitmap(b_peon_negro);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++)
			putpixel(b_peon_negro, i, j, palette_color[peon_negro[j][i]]);
	}
}

void draw_peon_negro(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'P') {
				draw_sprite(pantalla, b_peon_negro, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_peon_blanco(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'p') {
				draw_sprite(pantalla, b_peon_blanco, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_torre_blanca(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 't') {
				draw_sprite(pantalla, b_torre_blanca, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_torre_negra(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'T') {
				draw_sprite(pantalla, b_torre_negra, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_alfil_blanco(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'a') {
				draw_sprite(pantalla, b_alfil_blanco, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_alfil_negro(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'A') {
				draw_sprite(pantalla, b_alfil_negro, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_caballo_blanco(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'c') {
				draw_sprite(pantalla, b_caballo_blanco, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_caballo_negro(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'C') {
				draw_sprite(pantalla, b_caballo_negro, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_reina_blanca(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'w') {
				draw_sprite(pantalla, b_reina_blanca, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_rey_blanco(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'r') {
				draw_sprite(pantalla, b_rey_blanco, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_rey_negro(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'R') {
				draw_sprite(pantalla, b_rey_negro, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_reina_negra(BITMAP *pantalla, char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'W') {
				draw_sprite(pantalla, b_reina_negra, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void dibujar_peon_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]) {
	blit(pantalla, screen, 0, 0, 0, 0, 870, 667);
	if(pieza == 'p') {
		draw_sprite(pantalla, b_peon_blanco, x, y);
		masked_blit(b_peon_blanco, screen, 0, 0, x, y, 80, 80);
	} else {
		draw_sprite(pantalla, b_peon_negro, x, y);
		masked_blit(b_peon_negro, screen, 0, 0, x, y, 80, 80);
	}
	rest(RETARDO_MOVIMIENTO_PIEZA);
}

void dibujar_alfil_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]) {
	blit(pantalla, screen, 0, 0, 0, 0,870, 667);
	if(pieza == 'a') {
		draw_sprite(pantalla, b_alfil_blanco, x, y);
		masked_blit(b_alfil_blanco, screen, 0, 0, x, y, 80, 80);
	} else {
		draw_sprite(pantalla, b_alfil_negro, x, y);
		masked_blit(b_alfil_negro, screen, 0, 0, x, y, 80, 80);
	}
	rest(RETARDO_MOVIMIENTO_PIEZA);
}

void dibujar_caballo_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]) {
	blit(pantalla, screen, 0, 0, 0, 0, 870, 667);
	if(pieza == 'c') {
		draw_sprite(pantalla, b_caballo_blanco, x, y);
		masked_blit(b_caballo_blanco, screen, 0, 0, x, y, 80, 80);
	} else {
		draw_sprite(pantalla, b_caballo_negro, x, y);
		masked_blit(b_caballo_negro, screen, 0, 0, x, y, 80, 80);
	}
	rest(RETARDO_MOVIMIENTO_PIEZA);
}

void dibujar_torre_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]) {
	blit(pantalla, screen, 0, 0, 0, 0, 870, 667);
	if(pieza == 't') {
		draw_sprite(pantalla, b_torre_blanca, x, y);
		masked_blit(b_torre_blanca, screen, 0, 0, x, y, 80, 80);
	} else {
		draw_sprite(pantalla, b_torre_negra, x, y);
		masked_blit(b_torre_negra, screen, 0, 0, x, y, 80, 80);
	}
	rest(RETARDO_MOVIMIENTO_PIEZA);
}

void dibujar_reina_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]) {
	blit(pantalla, screen, 0, 0, 0, 0, 870, 667);
	if(pieza == 'w') {
		draw_sprite(pantalla, b_reina_blanca, x, y);
		masked_blit(b_reina_blanca, screen, 0, 0, x, y, 80, 80);
	} else {
		draw_sprite(pantalla, b_reina_negra, x, y);
		masked_blit(b_reina_negra, screen, 0, 0, x, y, 80, 80);
	}
	rest(RETARDO_MOVIMIENTO_PIEZA);
}

void dibujar_rey_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]) {
	blit(pantalla, screen, 0, 0, 0, 0, 870, 667);
	if(pieza == 'r') {
		draw_sprite(pantalla, b_rey_blanco, x, y);
		masked_blit(b_rey_blanco, screen, 0, 0, x, y, 80, 80);
	} else {
		draw_sprite(pantalla, b_rey_negro, x, y);
		masked_blit(b_rey_negro, screen, 0, 0, x, y, 80, 80);
	}
	rest(RETARDO_MOVIMIENTO_PIEZA);
}

void crear_piezas(void) {
	crear_torre_blanca();
	crear_torre_negra();
	crear_peon_blanco();
	crear_peon_negro();
	crear_alfil_blanco();
	crear_alfil_negro();
	crear_caballo_blanco();
	crear_caballo_negro();
	crear_reina_blanca();
	crear_reina_negra();
	crear_rey_blanco();
	crear_rey_negro();
}

void re_draw(BITMAP * pantalla, char campo[LADO][LADO]) {
	clear_bitmap(pantalla);
	draw_tablero(pantalla);
	draw_peon_blanco(pantalla, campo);
	draw_peon_negro(pantalla, campo);
	draw_torre_blanca(pantalla, campo);
	draw_torre_negra(pantalla, campo);
	draw_alfil_blanco(pantalla, campo);
	draw_alfil_negro(pantalla, campo);
	draw_caballo_blanco(pantalla, campo);
	draw_caballo_negro(pantalla, campo);
	draw_reina_blanca(pantalla ,campo);
	draw_reina_negra(pantalla, campo);
	draw_rey_blanco(pantalla, campo);
	draw_rey_negro(pantalla, campo);
}

void switcheo_draw_piezas(BITMAP * pantalla, char pieza, char campo[LADO][LADO]) {
	switch(pieza) {
		case 'p': draw_peon_blanco(pantalla, campo); break;
		case 'P': draw_peon_negro(pantalla, campo); break;
		case 't': draw_torre_blanca(pantalla, campo); break;
		case 'T': draw_torre_negra(pantalla, campo); break;
		case 'a': draw_alfil_blanco(pantalla, campo); break;
		case 'A': draw_alfil_negro(pantalla, campo); break;
		case 'c': draw_caballo_blanco(pantalla, campo); break;
		case 'C': draw_caballo_negro(pantalla, campo); break;
		case 'r': draw_rey_blanco(pantalla, campo); break;
		case 'R': draw_rey_negro(pantalla, campo); break;
		case 'w': draw_reina_blanca(pantalla, campo); break;
		case 'W': draw_reina_negra(pantalla, campo); break;
	}
}

void draw_cuadrado(int fila, int columna, char campo[LADO][LADO], int color_claro, int color_oscuro,  BITMAP * pantalla) {
	if(fila < 8 && columna < 8) {
		if(par_relativo(fila, columna)) {
			rect(pantalla, 11 + 80 * columna, 11 + 80 * fila, 90 + 80 * columna, 90 + 80 * fila, color_oscuro);
			rect(pantalla, 12 + 80 * columna, 12 + 80 * fila, 89 + 80 * columna, 89 + 80 * fila, color_oscuro);
			rect(pantalla, 13 + 80 * columna, 13 + 80 * fila, 88 + 80 * columna, 88 + 80 * fila, color_claro);
			rect(pantalla, 14 + 80 * columna, 14 + 80 * fila, 87 + 80 * columna, 87 + 80 * fila, color_claro);
		}
		else {
			rect(pantalla, 11 + 80 * columna, 11 + 80 * fila, 90 + 80 * columna, 90 + 80 * fila, color_oscuro);
			rect(pantalla, 12 + 80 * columna, 12 + 80 * fila, 89 + 80 * columna, 89 + 80 * fila, color_oscuro);
			rect(pantalla, 13 + 80 * columna, 13 + 80 * fila, 88 + 80 * columna, 88 + 80 * fila, color_claro);
			rect(pantalla, 14 + 80 * columna, 14 + 80 * fila, 87 + 80 * columna, 87 + 80 * fila, color_claro);
		}
	}
}

void liberar_memoria_piezas(BITMAP * pantalla) {
	destroy_bitmap(b_alfil_blanco);
	destroy_bitmap(b_alfil_negro);
	destroy_bitmap(b_peon_blanco);
	destroy_bitmap(b_peon_negro);
	destroy_bitmap(b_reina_blanca);
	destroy_bitmap(b_reina_negra);
	destroy_bitmap(b_caballo_blanco);
	destroy_bitmap(b_caballo_negro);
	destroy_bitmap(b_rey_blanco);
	destroy_bitmap(b_rey_negro);
	destroy_bitmap(b_torre_blanca);
	destroy_bitmap(b_torre_negra);
	destroy_bitmap(pantalla);
}
