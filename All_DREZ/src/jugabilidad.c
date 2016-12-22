#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "tablero_grafico.h"

#define LADO 8


void seleccionar(char campo[LADO][LADO]) {


	int tecla = 0;
	while(tecla != KEY_A) {
		rest(60);
		printf("%d %d\n" ,mouse_x,mouse_y);

		 if (mouse_b & 1)
			 printf("El botón izquierdo está pulsado\n");

		 if (!(mouse_b & 2))
			 printf("El botón derecho no está pulsado\n");
		 if(keypressed()) tecla = readkey() >> 8;
		re_draw(campo);
	}

}
