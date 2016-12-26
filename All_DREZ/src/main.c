#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "tablero_grafico.h"
#include "movimientos_peon.h"
#include "jugabilidad.h"
#include "inicializar.h"

#define LADO 8


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
