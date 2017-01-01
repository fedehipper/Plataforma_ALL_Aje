#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"
#include "jugabilidad.h"
#include "inicializar.h"

#define LADO 8

	char *allegico_xpm[] = {
	/* columns rows colors chars-per-pixel */
	"48 48 4 1",
	"  c red",
	". c black",
	"X c #808000000000",
	"o c None",
	/* pixels */
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"XXXXXX......XXXXXX......XXXXXX......XXXXXX......",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX",
	"......XXXXXX......XXXXXX......XXXXXX......XXXXXX"
};

#if defined ALLEGRO_WITH_XWINDOWS && defined ALLEGRO_USE_CONSTRUCTOR
	extern void *allegro_icon;
	CONSTRUCTOR_FUNCTION(void _set_allegro_icon(void));
	void _set_allegro_icon(void) {
		allegro_icon = allegico_xpm;
	}
#endif

BITMAP *pantalla;

int main(void) {
	allegro_init();

	set_color_depth(8);
	pantalla = create_bitmap(670, 670);
	clear_bitmap(pantalla);

	instalar_complementos();

	mostrar_display();

	char campo[LADO][LADO];

	inicializar_tablero(pantalla, campo);

	SAMPLE * sonido_mover = instalar_sonidos();

	// h vs h
	seleccionar(campo, sonido_mover, pantalla);

	desinstalar_complementos(sonido_mover);
	liberar_memoria_piezas(pantalla);
	allegro_exit();

	return EXIT_SUCCESS;
}
END_OF_MAIN();
