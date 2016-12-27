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
	"  c magenta",
	". c navy",
	"X c #808000000000",
	"o c None",
	/* pixels */
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	"XXXXX......XXXXXX......XXXXXX......XXXXXX.......",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX",
	".....XXXXXX......XXXXXX......XXXXXX......XXXXXXX"
};

#if defined ALLEGRO_WITH_XWINDOWS && defined ALLEGRO_USE_CONSTRUCTOR
	extern void *allegro_icon;
	CONSTRUCTOR_FUNCTION(void _set_allegro_icon(void));
	void _set_allegro_icon(void) {
		allegro_icon = allegico_xpm;
	}
#endif



int main(void) {
	allegro_init();

	instalar_complementos();

	mostrar_display();

	char campo[LADO][LADO];

	inicializar_tablero(campo);

	SAMPLE * sonido_mover = instalar_sonidos();

	// h vs h
	seleccionar(campo, sonido_mover);

	desinstalar_complementos();

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
