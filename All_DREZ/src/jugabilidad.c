#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>
#include "tablero_grafico.h"

#define LADO 8


void seleccionar(char campo[LADO][LADO]) {
	int fila = 0, columna = 0;

	int tecla = 0;
	while(tecla != KEY_A) {
		rest(115);


		 if (mouse_b & 1) {
			 fila = (mouse_y - 11) / 80;
			 columna = (mouse_x - 11) / 80;
			 printf("%d %d\n" ,fila,columna);
			 draw_selector_cuadrado(fila, columna);
		 }
		 // fila --> y
		 // columna --> x





		 if(keypressed()) tecla = readkey() >> 8;

		 //re_draw(campo);
	}


	// verificar la posicion y si clic, tomar el x e y y dividirlo por 10 y mostrar por pantalla luego de cliquear unicamente

}
