#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "tablero_grafico.h"

#define LADO 8


void seleccionar(char campo[LADO][LADO]) {


	int tecla = 0;
	while(tecla != KEY_A) {
		rest(120);


		 if (mouse_b & 1)
			 printf("%d %d\n" ,mouse_x,mouse_y);






		 if(keypressed()) tecla = readkey() >> 8;

		 //re_draw(campo);
	}


	// verificar la posicion y si clic, tomar el x e y y dividirlo por 10 y mostrar por pantalla luego de cliquear unicamente

}
