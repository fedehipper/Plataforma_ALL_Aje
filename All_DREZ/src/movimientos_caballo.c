#include <stdbool.h>

#define LADO 8

bool es_amigo_de_caballo(char rey, char otro) {
	return (rey == 'c')? otro == 'w' || otro == 'a' || otro == 'r' || otro == 't' || otro == 'c' || otro == 'p':
			otro == 'W' || otro == 'A' || otro == 'R' || otro == 'T' || otro == 'C' || otro == 'P';
}

bool movimiento_permitido_caballo(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	return ((fila_origen + 2 == fila_destino && columna_origen - 1 == columna_destino) ||
		    (fila_origen - 2 == fila_destino && columna_origen + 1 == columna_destino) ||
		    (columna_origen + 2 == columna_destino && fila_origen - 1 == fila_destino) ||
		    (columna_origen - 2 == columna_destino && fila_origen + 1 == fila_destino) ||
		    (fila_origen + 2 == fila_destino && columna_origen + 1 == columna_destino) ||
		    (fila_origen - 2 == fila_destino && columna_origen - 1 == columna_destino) ||
			(columna_origen + 2 == columna_destino && fila_origen + 1 == fila_destino) ||
			(columna_origen - 2 == columna_destino && fila_origen - 1 == fila_destino)) &&
			!es_amigo_de_caballo(campo[fila_origen][columna_origen], campo[fila_destino][columna_destino]);
}


bool es_jaque_caballo(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]) {
	bool es_jaque = false;
		if(pieza == 'c' && movimiento_permitido_caballo(fila_destino, columna_destino, f_rey_n, c_rey_n, campo)) {
			es_jaque = true;
		}

		if(pieza == 'C' && movimiento_permitido_caballo(fila_destino, columna_destino, f_rey_b, c_rey_b, campo)) {
			es_jaque = true;
		}
	return es_jaque;
}

