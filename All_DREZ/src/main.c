#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"
#include "jugabilidad.h"
#include "inicializar.h"
#include <string.h>
#include "lib_socket.h"
#include <CUnit/Basic.h>
#include <stdarg.h>
#include "../test/test.h"

#define LADO 8

char *allegico_xpm[] = {
	/* columns rows colors chars-per-pixel */
	"48 48 4 1",
	"  c red",
	". c brown",
	"X c orange",
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
	allegro_init();

	///////////////////////////////////////////MODO TEST//////////////////////////////////////////////////////////////////////
	if(argc > 1 && !strcmp(argv[1], "test")) {
		run_test();
	} else {
		int socket;
		set_color_depth(8);
		BITMAP * pantalla = create_bitmap(870, 667);
		clear_bitmap(pantalla);

		instalar_complementos();

		// por ahora se inicializa de esta manera, despues se desarrollara una pantalla de inicio
		// modo red --> ./ejecutable cliente ip ::::: ./ejecutable servidor ::::: ./ejecutable solitario ::::: ./ejecutable :::: ./ejecutable test
		mostrar_display();

		char campo[LADO][LADO];
		inicializar_tablero(pantalla, campo);
		SAMPLE * sonido_mover = instalar_sonidos();
		dibujar_seleccion_promocion(pantalla, 'w', 'W');
		blit(pantalla, screen, 0, 0, 0, 0, 870, 667);

		///////////////////////////////////////////MODO CLIENTE///////////////////////////////////////////////////////////////
		if(argc > 1 && !strcmp(argv[1], "cliente")) { // negras --> cliente
			printf("\n__MODO CLIENTE__\n");
			client_init(&socket, argv[2], "4005");
			seleccionar_en_red(campo, sonido_mover, pantalla, 'c', &socket);
			close(socket);
		}

		///////////////////////////////////////////MODO SERVIDOR///////////////////////////////////////////////////////////////
		if(argc > 1 && !strcmp(argv[1], "servidor")) { // blancas --> servidor
			printf("\n__MODO SERVIDOR__\n");
			server_init(&socket, "4005");
			server_acept(socket, &socket);
			printf("cliente aceptado...\n");
			seleccionar_en_red(campo, sonido_mover, pantalla, 's', &socket);
			close(socket);
		}

		////////////////////////////////////////////MODO SOLITARIO Y MODO VS MAQUINA///////////////////////////////////////////
		(argc > 1 && !strcmp(argv[1], "solitario")) ? seleccionar_en_solitario(campo, sonido_mover, pantalla) :
			seleccionar_en_solitario(campo, sonido_mover, pantalla); // por ahora

		desinstalar_complementos(sonido_mover);
		liberar_memoria_piezas(pantalla);
	}

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
