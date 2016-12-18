#include <allegro.h>

#define ESCALA 10

void draw_bordes() {
	rect(screen, ESCALA, ESCALA, 650, 650, palette_color[15]);
}

void draw_lineas_verticales() {
	rect(screen, ESCALA, ESCALA, 90, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 170, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 250, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 330, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 410, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 490, 650, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 570, 650, palette_color[15]);
}

void draw_lineas_horizontales() {
	rect(screen, ESCALA, ESCALA, 650, 90, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 170, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 250, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 330, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 410, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 490, palette_color[15]);
	rect(screen, ESCALA, ESCALA, 650, 570, palette_color[15]);
}

void draw_coordenadas() {
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

void draw_tablero() {
	draw_bordes();
	draw_lineas_verticales();
	draw_lineas_horizontales();
	draw_coordenadas();
}
