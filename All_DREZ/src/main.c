#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"
#include "jugabilidad.h"

#define LADO 8

int main(void) {

	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();
	set_gfx_mode(GFX_SAFE, 670, 670, 0, 0);
	show_mouse(screen);
	crear_piezas();
	draw_tablero();
	char campo[LADO][LADO];

	tablero_en_blanco(campo);
	inicializar_posicion_piezas(campo);
	re_draw(campo);



	seleccionar(campo);


	readkey();

	avanzar_uno(7, 'f', 'N', campo);

	re_draw(campo);

	readkey();

	allegro_exit();

	return EXIT_SUCCESS;
}
