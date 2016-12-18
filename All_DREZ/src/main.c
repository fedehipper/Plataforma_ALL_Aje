#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"

#define ESCALA 10

int main(void) {

	allegro_init();
	install_keyboard();
	set_gfx_mode(GFX_SAFE, 670, 670, 0, 0);
	draw_tablero();
	char campo[8][8];
	int i,j;
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 8 ; j++) {
			campo[i][j] = 'p';
		}
	}

	crear_pieza();
	draw_pieza(campo);





	readkey();
	allegro_exit();

	return EXIT_SUCCESS;
}
