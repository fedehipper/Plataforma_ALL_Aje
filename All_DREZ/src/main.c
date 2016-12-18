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




	readkey();
	allegro_exit();

	return EXIT_SUCCESS;
}
