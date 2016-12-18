#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"

#define ESCALA 10

int main(void) {

	allegro_init();
	install_keyboard();
	set_gfx_mode(GFX_SAFE, 670, 670, 0, 0);
	crear_piezas();
	draw_tablero();
	char campo[8][8];

	tablero_en_blanco(campo);
	inicializar_posicion_piezas(campo);
	re_draw(campo);






//
//	rectfill(screen, aux_1, aux_1, aux_2, aux_2, 4);
//	rectfill(screen, aux_1 + 160, aux_1, aux_2 + 160, aux_2, 4);
//	rectfill(screen, aux_1 + 320, aux_1, aux_2 + 320, aux_2, 4);
//	rectfill(screen, aux_1 + 480, aux_1, aux_2 + 480, aux_2, 4);




	readkey();

	avanzar_uno(2, 'f', 'B', campo);

	re_draw(campo);

	readkey();

	allegro_exit();

	return EXIT_SUCCESS;
}
