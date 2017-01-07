#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "piezas.h"

#define ESCALA 10
#define LADO 8
#define LADO_PIEZA 71
#define COLOR_LINEAS 42
#define COLOR_CUADRADOS 4
#define CARACTER_A_ENTERO 97
#define RETARDO_MOVIMIENTO_PIEZA 10

BITMAP *b_peon_blanco, *b_peon_negro, *b_torre_blanca, *b_torre_negra, *b_alfil_blanco, *b_alfil_negro, *b_caballo_blanco,
	   *b_caballo_negro, *b_reina_blanca, *b_reina_negra, *b_rey_blanco, *b_rey_negro;

void draw_bordes(BITMAP *pantalla) {
	rect(pantalla, ESCALA, ESCALA, 650, 650, palette_color[COLOR_LINEAS]);
}

void draw_lineas_verticales(BITMAP *pantalla) {
	rect(pantalla, ESCALA, ESCALA, 90, 650, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 170, 650, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 250, 650, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 330, 650, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 410, 650, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 490, 650, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 570, 650, palette_color[COLOR_LINEAS]);
}

void draw_lineas_horizontales(BITMAP *pantalla) {
	rect(pantalla, ESCALA, ESCALA, 650, 90, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 650, 170, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 650, 250, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 650, 330, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 650, 410, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 650, 490, palette_color[COLOR_LINEAS]);
	rect(pantalla, ESCALA, ESCALA, 650, 570, palette_color[COLOR_LINEAS]);
}

void draw_coordenadas(BITMAP * pantalla) {
	textprintf_justify_ex(pantalla, font, 45, 10, 655, 0, 15, 0, "A         B         C         D         E         F         G         H");
	textprintf_justify_ex(pantalla, font, 655, 10, 45, 0, 15, 0, "1");
	textprintf_justify_ex(pantalla, font, 655, 10, 125, 0, 15, 0, "2");
	textprintf_justify_ex(pantalla, font, 655, 10, 205, 0, 15, 0, "3");
	textprintf_justify_ex(pantalla, font, 655, 10, 285, 0, 15, 0, "4");
	textprintf_justify_ex(pantalla, font, 655, 10, 365, 0, 15, 0, "5");
	textprintf_justify_ex(pantalla, font, 655, 10, 445, 0, 15, 0, "6");
	textprintf_justify_ex(pantalla, font, 655, 10, 525, 0, 15, 0, "7");
	textprintf_justify_ex(pantalla, font, 655, 10, 605, 0, 15, 0, "8");
}

bool impar_relativo(int i, int j) {
	return fmod(i + j, 2)  > 0;
}

bool par_relativo(int i, int j) {
	return fmod(i + j, 2) == 0;
}

// si es fila impar y posicion de columna impar entonces se pinta
void draw_cuadros_tablero(BITMAP *pantalla) {
	int aux_1 = 11, aux_2 = 89, i, j;
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 8 ; j++) {
			if(impar_relativo(i, j))
				rectfill(pantalla, aux_1 + 80 * i, aux_1 + 80 * j, aux_2 + 80 * i, aux_2 + 80 * j, 16);
			else
				rectfill(pantalla, aux_1 + 80 * i, aux_1 + 80 * j, aux_2 + 80 * i, aux_2 + 80 * j, COLOR_CUADRADOS);
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

void draw_tablero(BITMAP *pantalla) {
	draw_lineas_verticales(pantalla);
	draw_lineas_horizontales(pantalla);
	draw_coordenadas(pantalla);
	draw_cuadros_tablero(pantalla);
	draw_bordes(pantalla);
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
	blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
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
	blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
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
	blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
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
	blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
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
	blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
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
	blit(pantalla, screen, 0, 0, 0, 0, 670, 670);
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
		case 'p': draw_peon_blanco(pantalla, campo);
		break;
		case 'P': draw_peon_negro(pantalla, campo);
		break;
		case 't': draw_torre_blanca(pantalla, campo);
		break;
		case 'T': draw_torre_negra(pantalla, campo);
		break;
		case 'a': draw_alfil_blanco(pantalla, campo);
		break;
		case 'A': draw_alfil_negro(pantalla, campo);
		break;
		case 'c': draw_caballo_blanco(pantalla, campo);
		break;
		case 'C': draw_caballo_negro(pantalla, campo);
		break;
		case 'r': draw_rey_blanco(pantalla, campo);
		break;
		case 'R': draw_rey_negro(pantalla, campo);
		break;
		case 'w': draw_reina_blanca(pantalla, campo);
		break;
		case 'W': draw_reina_negra(pantalla, campo);
		break;
	}
}

// para que no quede seleccionado el cuadro de seleccion se dibuja nuevamente el rojo(4) o negro(16), rojo_claro(12), negro_claro(24)
void draw_cuadrado(int fila, int columna, char campo[LADO][LADO], int color_claro, int color_oscuro, bool dibujar_pieza, BITMAP * pantalla) {
	if(fila != 8 && columna != 8) {
		if(par_relativo(fila, columna))
			rectfill(pantalla, 11 + 80 * columna , 11 + 80 * fila, 89 + 80 * columna, 89 + 80 * fila, color_claro);
		else
			rectfill(pantalla, 11 + 80 * columna , 11 + 80 * fila, 89 + 80 * columna, 89 + 80 * fila, color_oscuro);
		if(dibujar_pieza) {
			if(campo[fila][columna] != ' ') {
				switcheo_draw_piezas(pantalla, campo[fila][columna], campo);
			}
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

void menu(BITMAP * pantalla, int mouse_y, int mouse_x, int *arr) {
	rectfill(pantalla, mouse_x, mouse_y, mouse_x + 160, mouse_y + 50, 29);
	// 0 - 3 seleccion promocion
	arr[0] = mouse_x;
	arr[1] = mouse_y + 28;
	arr[2] = mouse_x + 160;
	arr[3] = mouse_y + 48;
	// 4 - 7 menu padre
	arr[4] = mouse_x;
	arr[5] = mouse_y;
	arr[6] = mouse_x + 160;
	arr[7] = mouse_y + 50;

	line(pantalla, mouse_x + 2, mouse_y + 25, mouse_x + 158 , mouse_y + 25, 27);
}

void menu_seleccion_promocion(BITMAP *pantalla, int mouse_x, int mouse_y, bool seleccion) {
	if(seleccion) {
		rectfill(pantalla, mouse_x, mouse_y + 2, mouse_x + 160, mouse_y + 22, 15);
		textprintf_centre_ex(pantalla, font, mouse_x + 52, mouse_y + 9, 17, 15, "Promocion");
	}
	else {
		rectfill(pantalla, mouse_x, mouse_y + 2, mouse_x + 160, mouse_y + 22, 29);
		textprintf_centre_ex(pantalla, font, mouse_x + 52, mouse_y + 9, 17, 29, "Promocion");
	}
	triangle(pantalla, mouse_x + 150, mouse_y + 8, mouse_x + 155, mouse_y + 13, mouse_x + 150, mouse_y + 18, 21);
}

void menu_seleccion_cerrar(BITMAP * pantalla, int mouse_x, int mouse_y, bool seleccion) {
	if(seleccion) {
		rectfill(pantalla, mouse_x, mouse_y + 28, mouse_x + 160, mouse_y + 48, 15);
		textprintf_centre_ex(pantalla, font, mouse_x + 40, mouse_y + 34, 17, 15, "Cerrar");
	}
	else {
		rectfill(pantalla, mouse_x, mouse_y + 28, mouse_x + 160, mouse_y + 48, 29);
		textprintf_centre_ex(pantalla, font, mouse_x + 40, mouse_y + 34, 17, 29, "Cerrar");
	}
}

void menu_blanco_y_negro(BITMAP *pantalla, int * arr, bool supera_limite_pantalla) {
	// el array tiene la posicion de donde se mostro el menu padre, se puede verificar con este si se va a dibujar el menu hijo
	// en el lado izquierdo o derecho
	if(arr[6] + 100 > 600) {
		rectfill(pantalla, arr[6] - 262, arr[1] - 28, arr[6] - 162, arr[1] + 22, 29);
		line(pantalla, arr[4] - 4, arr[5] + 25, arr[4] - 101 , arr[5] + 25, 27);
		textprintf_centre_ex(pantalla, font, arr[4] - 58, arr[5] + 9, 17, 29, "Blanco");
		textprintf_centre_ex(pantalla, font, arr[4] - 61, arr[5] + 35, 17, 29, "Negro");
	} else {
		rectfill(pantalla, arr[6] + 2, arr[1] - 28, arr[6] + 100, arr[1] + 22, 29);
		line(pantalla, arr[4] + 163, arr[5] + 25, arr[4] + 258 , arr[5] + 25, 27);
		textprintf_centre_ex(pantalla, font, arr[4] + 200, arr[5] + 9, 17, 29, "Blanco");
		textprintf_centre_ex(pantalla, font, arr[4] + 197, arr[5] + 35, 17, 29, "Negro");
	}




}


