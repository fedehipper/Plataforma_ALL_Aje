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

void draw_tablero() {
	draw_bordes();
	draw_lineas_verticales();
	draw_lineas_horizontales();
}
