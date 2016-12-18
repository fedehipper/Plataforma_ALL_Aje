#include <allegro.h>
#include "piezas.h"

#define ESCALA 10
#define LADO 8
#define LADO_PIEZA 40

BITMAP *pieza;

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

void draw_tablero(void) {
	draw_bordes();
	draw_lineas_verticales();
	draw_lineas_horizontales();
	draw_coordenadas();
}

void crear_pieza(void) {
	int i, j;
	pieza = create_bitmap(80, 80);
	clear_bitmap(pieza);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++)
			putpixel(pieza, i, j, palette_color[peon[j][i]]);
	}
}

void draw_pieza(char campo[LADO][LADO]) {
	int i, j;
	clear_bitmap(screen);
	draw_tablero();
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'p') {
				draw_sprite(screen, pieza, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}






