#include <allegro.h>
#include "piezas.h"

#define ESCALA 10
#define LADO 8
#define LADO_PIEZA 40
#define COLOR_LINEAS 42
#define COLOR_CUADRADOS 4

BITMAP *b_peon_blanco, *b_peon_negro, *b_torre_blanca, *b_torre_negra, *b_alfil_blanco, *b_alfil_negro, *b_caballo_blanco,
	   *b_caballo_negro, *b_reina_blanca;

void draw_bordes(void) {
	rect(screen, ESCALA, ESCALA, 650, 650, palette_color[COLOR_LINEAS]);
}

void draw_lineas_verticales(void) {
	rect(screen, ESCALA, ESCALA, 90, 650, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 170, 650, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 250, 650, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 330, 650, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 410, 650, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 490, 650, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 570, 650, palette_color[COLOR_LINEAS]);
}

void draw_lineas_horizontales(void) {
	rect(screen, ESCALA, ESCALA, 650, 90, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 650, 170, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 650, 250, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 650, 330, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 650, 410, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 650, 490, palette_color[COLOR_LINEAS]);
	rect(screen, ESCALA, ESCALA, 650, 570, palette_color[COLOR_LINEAS]);
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

// si es fila impar y posicion de columna impar entonces se pinta
void draw_cuadros_tablero(void) {
	int aux_1 = 11, aux_2 = 89, i, j;
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 8 ; j++) {
			if((i == 0 || i == 2 || i == 4 || i == 6) && (j == 0 || j == 2 || j == 4 || j == 6))
				rectfill(screen, aux_1 + 80 * i, aux_1 + 80 * j, aux_2 + 80 * i, aux_2 + 80 * j, COLOR_CUADRADOS);
			else if((i == 1 || i == 3 || i == 5 || i == 7) && (j == 1 || j == 3 || j == 5 || j == 7))
				rectfill(screen, aux_1 + 80 * i, aux_1 + 80 * j, aux_2 + 80 * i, aux_2 + 80 * j, COLOR_CUADRADOS);
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

// piezas en minuscula --> blancas y mayuscula --> negras
void inicializar_posicion_peones(char campo[LADO][LADO]) {
	int i;
	for(i = 0 ; i < 8 ; i++)
		campo[1][i] = 'p';
	for(i = 0 ; i < 8 ; i++)
		campo[6][i] = 'P';
}

void inicializar_posicion_reinas(char campo[LADO][LADO]) {
	campo[0][4] = 'w';
	campo[7][4] = 'W';
}

void inicializar_posicion_alfiles(char campo[LADO][LADO]) {
	campo[0][2] = 'a';
	campo[0][5] = 'a';
	campo[7][2] = 'A';
	campo[7][5] = 'A';
}

void inicializar_posicion_torres(char campo[LADO][LADO]) {
	campo[0][0] = 't';
	campo[0][7] = 't';
	campo[7][0] = 'T';
	campo[7][7] = 'T';
}

void inicializar_posicion_caballos(char campo[LADO][LADO]) {
	campo[0][1] = 'c';
	campo[0][6] = 'c';
	campo[7][1] = 'C';
	campo[7][6] = 'C';
}

void inicializar_posicion_piezas(char campo[LADO][LADO]) {
	inicializar_posicion_peones(campo);
	inicializar_posicion_torres(campo);
	inicializar_posicion_alfiles(campo);
	inicializar_posicion_caballos(campo);
	inicializar_posicion_reinas(campo);
}

void draw_tablero(void) {
	draw_lineas_verticales();
	draw_lineas_horizontales();
	draw_coordenadas();
	draw_cuadros_tablero();
	draw_bordes();
}

void crear_caballo_blanco(void) {
	int i, j;
	b_caballo_blanco = create_bitmap(80, 80);
	clear_bitmap(b_caballo_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_caballo_blanco, i, j, palette_color[caballo_blanco[j][i]]);
		}
	}
}

void crear_reina_blanca(void) {
	int i, j;
	b_reina_blanca = create_bitmap(80, 80);
	clear_bitmap(b_reina_blanca);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_reina_blanca, i, j, palette_color[reina_blanca[j][i]]);
		}
	}
}

void crear_caballo_negro(void) {
	int i, j;
	b_caballo_negro = create_bitmap(80, 80);
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
	for(i = 0 ; i < LADO_PIEZA + 30 ; i++) {
		for(j = 0 ; j < LADO_PIEZA + 30 ; j++) {
			putpixel(b_torre_blanca, i, j, palette_color[torre_blanca[j][i]]);
		}
	}
}

void crear_alfil_blanco(void) {
	int i, j;
	b_alfil_blanco = create_bitmap(80, 80);
	clear_bitmap(b_alfil_blanco);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_alfil_blanco, i, j, palette_color[alfil_blanco[j][i]]);
		}
	}
}

void crear_alfil_negro(void) {
	int i, j;
	b_alfil_negro = create_bitmap(80, 80);
	clear_bitmap(b_alfil_negro);
	for(i = 0 ; i < LADO_PIEZA ; i++) {
		for(j = 0 ; j < LADO_PIEZA ; j++) {
			putpixel(b_alfil_negro, i, j, palette_color[alfil_negro[j][i]]);
		}
	}
}

void crear_torre_negra(void) {
	int i, j;
	b_torre_negra = create_bitmap(80, 80);
	clear_bitmap(b_torre_negra);
	for(i = 0 ; i < LADO_PIEZA + 30 ; i++) {
		for(j = 0 ; j < LADO_PIEZA + 30; j++) {
			putpixel(b_torre_negra, i, j, palette_color[torre_negra[j][i]]);
		}
	}
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

void draw_torre_blanca(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 't') {
				draw_sprite(screen, b_torre_blanca, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_torre_negra(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'T') {
				draw_sprite(screen, b_torre_negra, j * 80 + 15, i * 80 + 15);
			}
		}
	}
}

void draw_alfil_blanco(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'a') {
				draw_sprite(screen, b_alfil_blanco, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}

void draw_alfil_negro(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'A') {
				draw_sprite(screen, b_alfil_negro, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}

void draw_caballo_blanco(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'c') {
				draw_sprite(screen, b_caballo_blanco, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}

void draw_caballo_negro(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'C') {
				draw_sprite(screen, b_caballo_negro, j * 80 + 30, i * 80 + 30);
			}
		}
	}
}

void draw_reina_blanca(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(campo[i][j] == 'w') {
				draw_sprite(screen, b_reina_blanca, j * 80 + 30, i * 80 + 30);
			}
		}
	}
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
}

void re_draw(char campo[LADO][LADO]) {
	clear_bitmap(screen);
	draw_tablero();
	draw_peon_blanco(campo);
	draw_peon_negro(campo);
	draw_torre_blanca(campo);
	draw_torre_negra(campo);
	draw_alfil_blanco(campo);
	draw_alfil_negro(campo);
	draw_caballo_blanco(campo);
	draw_caballo_negro(campo);
	draw_reina_blanca(campo);
}





