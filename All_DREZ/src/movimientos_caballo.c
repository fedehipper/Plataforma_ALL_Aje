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

bool es_hacke_caballo(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	int i, j;
	bool es_hacke = false;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(movimiento_permitido_caballo(fila_origen, columna_origen, i, j, campo)) {
				if(campo[fila_origen][columna_origen] == 'c' && campo[i][j] == 'R') {
					es_hacke = true;
					break;
				}
				if(campo[fila_origen][columna_origen] == 'C' && campo[i][j] == 'r') {
					es_hacke = true;
					break;
				}
			}
		}
		if(es_hacke) break;
	}
	return es_hacke;
}
