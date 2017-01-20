#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"
#include "jugabilidad.h"
#include "inicializar.h"
#include <string.h>
#include "lib_socket.h"

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


int main(int argc, char **argv) {
	int socket;
	allegro_init();
	set_color_depth(8);
	BITMAP * pantalla = create_bitmap(870, 667);
	clear_bitmap(pantalla);

	instalar_complementos();
	mostrar_display();

	char campo[LADO][LADO];
	inicializar_tablero(pantalla, campo);
	SAMPLE * sonido_mover = instalar_sonidos();

	// modo red --> ./cliente ip o ./servidor
	if(argc > 1 && !strcmp(argv[1], "cliente")) { // negras --> cliente
		printf("\n__MODO CLIENTE__\n");
		client_init(&socket, argv[2], "4444");

		seleccionar_en_red(campo, sonido_mover, pantalla, 'c', &socket);
		close(socket);
	} else if(argc > 1 && !strcmp(argv[1], "servidor")) { // blancas --> servidor
		printf("\n__MODO SERVIDOR__\n");
		server_init(&socket, "4444");

		server_acept(socket, &socket);
		printf("cliente aceptado...\n");

		seleccionar_en_red(campo, sonido_mover, pantalla, 's', &socket);
		close(socket);
	} else {
		// por ahora dejo el modo test, hay que hacer el algoritmo poda alfa-beta minimax
		seleccionar(campo, sonido_mover, pantalla);
	}

	desinstalar_complementos(sonido_mover);
	liberar_memoria_piezas(pantalla);
	allegro_exit();

	return EXIT_SUCCESS;
}
END_OF_MAIN();
