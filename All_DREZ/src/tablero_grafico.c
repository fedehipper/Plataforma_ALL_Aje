#include <allegro.h>
#include "piezas.h"

#define ESCALA 10
#define LADO 8
#define LADO_PIEZA 40

BITMAP *b_peon_blanco, *b_peon_negro;

void draw_bordes(void) {
	rect(screen, ESCALA, ESCALA, 650, 650, palette_color[15]);
}

void draw_lineas_verticales(void) {
	rect(screen, ESCALA, ESCALA, 90, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 170, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 250, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 330, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 410, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 490, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 570, 650, palette_color[15]);
}

void draw_lineas_horizontales(void) {
	rect(screen, ESCALA, ESCALA, 650, 90, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 170, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 250, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 330, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 410, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 490, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 570, palette_color[15]);
}

void draw_coordenadas(void) {
	textprintf_justify_ex(screen, font, 45, 10, 655, 0, 15, 0, "A         B         C         D         E         F         G         H");
	textprintf_justify_ex(screen, font, 655, 10, 45, 0, 15, 0, "1");
	textprintf_justify_ex(screen, font, 655, 10, 125, 0, 15, 0, "2");
	textprintf_justify_ex(screen, font, 655, 10, 205, 0, 15, 0, "3");
	textprintf_justify_ex(screen, font, 655, 10, 285, 0, 15, 0, "4");
	textprintf_justify_ex(screen, font, 655, 10, 365, 0, 15, 0, "5");
	textprintf_justify_ex(screen, font, 655, 10, 445, 0, 15, 0, "6");
	textprintf_justify_ex(screen, font, 655, 10, 525, 0, 15, 0, "7");
	textprintf_justify_ex(screen, font, 655, 10, 605, 0, 15, 0, "8");
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
	// piezas en minuscula --> blancas y mayuscula --> negras
	int i;
	for(i = 0 ; i < 8 ; i++) {
		campo[1][i] = 'p';
	}
	for(i = 0 ; i < 8 ; i++) {
		campo[6][i] = 'P';
	}
}

void inicializar_posicion_piezas(char campo[LADO][LADO]) {
	inicializar_posicion_peones(campo);
}

void draw_tablero(void) {
	draw_bordes();
	draw_lineas_verticales();
	draw_lineas_horizontales();
	draw_coordenadas();
}

void crear_peon_blanco(void) {
	int i, j;
	b_peon_blanco = create_bitmap(80, 80);
	clear_bitmap(b_peon_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++)
			putpixel(b_peon_blanco, i, j, palette_color[peon_blanco[j][i]]);
	}
}

void crear_peon_negro(void) {
	int i, j;
	b_peon_negro = create_bitmap(80, 80);
	clear_bitmap(b_peon_negro);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++)
			putpixel(b_peon_negro, i, j, palette_color[peon_negro[j][i]]);
	}
}

void draw_peon_negro(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'P') {
				draw_sprite(screen, b_peon_negro, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}

void draw_peon_blanco(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'p') {
				draw_sprite(screen, b_peon_blanco, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}

void crear_piezas(void) {
	crear_peon_blanco();
	crear_peon_negro();
}

void re_draw(char campo[LADO][LADO]) {
	clear_bitmap(screen);
	draw_tablero();
	draw_peon_blanco(campo);
	draw_peon_negro(campo);
}





