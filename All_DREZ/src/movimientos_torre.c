#include <stdbool.h>

#define LADO 8

bool es_amigo_de_torre(char torre, char otro) {
	if(torre == 't') {
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
		return fila_origen < fila_destino;
	} else {
		return fila_origen > fila_destino;
	}
}

bool es_arriba(int fila_origen, int columna_origen, int fila_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return fila_origen > fila_destino;
	} else {
		return fila_origen < fila_destino;
	}
}

bool es_a_la_izquierda(int fila_origen, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return columna_origen > columna_destino;
	} else {
		return columna_origen < columna_destino;
	}
}

bool es_a_la_derecha(int fila_origen, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
	if(color_torre(fila_origen, columna_origen, campo) == 't') {
		return columna_origen < columna_destino;
	} else {
		return columna_origen > columna_destino;
	}
}

bool puede_ir_arriba(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila_origen, columna, campo) == 't') {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
}

bool puede_ir_abajo(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila_origen, columna, campo) == 't') {
		distancia = fila_destino - fila_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen + i][columna] != ' ') {
				break;
			}
		}
	} else {
		distancia = fila_origen - fila_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila_origen - i][columna] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
}


bool puede_ir_izquierda(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila, columna_origen, campo) == 't') {
		distancia = columna_origen - columna_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen - i] != ' ') {
				break;
			}
		}
	} else {
		distancia = columna_destino - columna_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen + i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
}

bool puede_ir_derecha(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
	int i = 0, distancia = 0;
	if(color_torre(fila, columna_origen, campo) == 't') {
		distancia = columna_destino - columna_origen;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen + i] != ' ') {
				break;
			}
		}
	} else {
		distancia = columna_origen - columna_destino;
		for(i = 1 ; i < distancia ; i++) {
			if(campo[fila][columna_origen - i] != ' ') {
				break;
			}
		}
	}
	return i == distancia && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
}


bool movimiento_permitido_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	if(es_arriba(fila_origen, columna_origen,  fila_destino, campo)) {
		return puede_ir_arriba(fila_origen, fila_destino, columna_origen, campo);
	} else if(es_abajo(fila_origen, columna_origen,  fila_destino, campo)) {
		return puede_ir_abajo(fila_origen, fila_destino, columna_origen, campo);
	} else if(es_a_la_derecha(fila_origen, columna_origen, columna_destino, campo)) {
		return puede_ir_derecha(columna_origen, columna_destino, fila_origen, campo);
	} else if(es_a_la_izquierda(fila_origen, columna_origen, columna_destino, campo)) {
		return puede_ir_izquierda(columna_origen, columna_destino, fila_origen, campo);
	} else
		return false;
}






