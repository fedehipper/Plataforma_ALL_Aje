#include <stdbool.h>

#define LADO 8

bool es_amigo_de_torre(char peon, char otro) {
	if(peon == 't') {
		return otro == 'w' || otro == 'a' || otro == 'r' || otro == 'p' || otro == 'c' || otro == 't';
	} else {
		return otro == 'W' || otro == 'A' || otro == 'R' || otro == 'P' || otro == 'C' || otro == 'T';
	}
}


char color_torre(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_abajo(int fila_origen, int columna_origen, int fila_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return (fila_origen - fila_destino) * (-1) > 0;
	} else {
		return (fila_origen - fila_destino) > 0;
	}
}

bool es_arriba(int fila_origen, int columna_origen, int fila_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return (fila_origen - fila_destino) > 0;
	} else {
		return (fila_origen - fila_destino) * (-1) > 0;
	}
}

bool es_a_la_izquierda(int fila_origen, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return (columna_origen - columna_destino) > 0;
	} else {
		return (columna_origen - columna_destino) * (-1) > 0;
	}
}

bool es_a_la_derecha(int fila_origen, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return (columna_origen - columna_destino) * (-1) > 0;
	} else {
		return (columna_origen - columna_destino) > 0;
	}
}

bool puede_ir_arriba(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila_origen, columna, campo) == 't') {
		distancia = fila_origen - fila_destino;
	} else {
		distancia = fila_destino - fila_origen;
	}
	for(i = 1 ; i <= distancia ; i++) {
		if(campo[i][columna] != ' ') {
			break;
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
}

bool puede_ir_abajo(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila_origen, columna, campo) == 't') {
		distancia = fila_destino - fila_origen;
	} else {
		distancia = fila_origen - fila_destino;
	}
	for(i = 1 ; i <= distancia ; i++) {
		if(campo[i][columna] != ' ') {
			break;
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
}


bool puede_ir_horizontal(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
	int i = 0;
	for(i = columna_origen + 1 ; i < columna_destino ; i++) {
		if(campo[fila][i] != ' ') {
			break;
		}
	}
	return i == columna_destino - 1 && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
}


bool movimiento_permitido_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(es_arriba(fila_origen, columna_origen,  fila_destino, campo)) {
		return puede_ir_arriba(fila_origen, fila_destino, columna_origen, campo);
	}
	if(es_abajo(fila_origen, columna_origen,  fila_destino, campo)) {
		return puede_ir_abajo(fila_origen, fila_destino, columna_origen, campo);
	}
	if(es_a_la_derecha(fila_origen, columna_origen, columna_destino, campo)) {
		return puede_ir_horizontal(columna_origen, columna_destino, fila_origen, campo);
	}
	if(es_a_la_izquierda(fila_origen, columna_origen, columna_destino, campo)) {
		return puede_ir_horizontal(columna_origen, columna_destino, fila_origen, campo);
	} else
		return false;
}






