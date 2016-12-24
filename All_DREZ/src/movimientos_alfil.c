#include <stdbool.h>

#define LADO 8

bool es_amigo_de_alfil(char alfil, char otro) {
	if(alfil == 'a') {
		return otro == 'w' || otro == 'a' || otro == 'r' || otro == 'p' || otro == 'c' || otro == 't';
	} else {
		return otro == 'W' || otro == 'A' || otro == 'R' || otro == 'P' || otro == 'C' || otro == 'T';
	}
}

char color_alfil(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_superior_derecha_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen > fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = columna_destino + 1;
			distancia = (distancia_horizontal < distancia_vertical) ? distancia_horizontal : distancia_horizontal;

			for(i = 0 ; i < distancia ; i++) {
				if(fila_origen - i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen < fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = columna_origen + 1;
			distancia_vertical = 7 - columna_destino;
			distancia = (distancia_horizontal < distancia_vertical) ? distancia_horizontal : distancia_horizontal;

			for(i = 0 ; i < distancia ; i++) {
				if(fila_origen + i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool es_superior_izquierda_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen > fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = columna_origen + 1;
			distancia_vertical = columna_destino + 1;
			distancia = (distancia_horizontal < distancia_vertical) ? distancia_horizontal : distancia_horizontal;

			for(i = 0 ; i < distancia ; i++) {
				if(fila_origen - i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen < fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = 7 - columna_destino;
			distancia = (distancia_horizontal < distancia_vertical) ? distancia_horizontal : distancia_horizontal;

			for(i = 0 ; i < distancia ; i++) {
				if(fila_origen + i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool es_inferior_derecha_de_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
	int i = 0, distancia_vertical = 0, distancia_horizontal = 0, distancia = 0;
	bool flag = false;
	if(color_alfil(fila_origen, columna_origen, campo) == 'a') {
		if(fila_origen > fila_destino && columna_origen < columna_destino) {
			distancia_horizontal = columna_origen + 1;
			distancia_vertical = columna_destino + 1;
			distancia = (distancia_horizontal < distancia_vertical) ? distancia_horizontal : distancia_horizontal;

			for(i = 0 ; i < distancia ; i++) {
				if(fila_origen - i == fila_destino && columna_origen - i == columna_destino) {
					flag = true;
				}
			}
		}
	} else {
		if(fila_origen < fila_destino && columna_origen > columna_destino) {
			distancia_horizontal = 7 - columna_origen;
			distancia_vertical = 7 - columna_destino;
			distancia = (distancia_horizontal < distancia_vertical) ? distancia_horizontal : distancia_horizontal;

			for(i = 0 ; i < distancia ; i++) {
				if(fila_origen + i == fila_destino && columna_origen + i == columna_destino) {
					flag = true;
				}
			}
		}
	}
	return flag;
}

//
//bool es_a_la_izquierda_de_torre(int fila_origen, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
//	if(color_torre(fila_origen, columna_origen, campo) == 't') {
//		return columna_origen > columna_destino;
//	} else {
//		return columna_origen < columna_destino;
//	}
//}
//
//bool es_a_la_derecha_de_torre(int fila_origen, int columna_origen, int columna_destino, char campo[LADO][LADO]) {
//	if(color_torre(fila_origen, columna_origen, campo) == 't') {
//		return columna_origen < columna_destino;
//	} else {
//		return columna_origen > columna_destino;
//	}
//}
//
//bool puede_ir_arriba_torre(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
//	int i = 0, distancia = 0;
//	if(color_torre(fila_origen, columna, campo) == 't') {
//		distancia = fila_origen - fila_destino;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila_origen - i][columna] != ' ') {
//				break;
//			}
//		}
//	} else {
//		distancia = fila_destino - fila_origen;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila_origen + i][columna] != ' ') {
//				break;
//			}
//		}
//	}
//	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
//}
//
//bool puede_ir_abajo_torre(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {
//	int i = 0, distancia = 0;
//	if(color_torre(fila_origen, columna, campo) == 't') {
//		distancia = fila_destino - fila_origen;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila_origen + i][columna] != ' ') {
//				break;
//			}
//		}
//	} else {
//		distancia = fila_origen - fila_destino;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila_origen - i][columna] != ' ') {
//				break;
//			}
//		}
//	}
//	return i == distancia && !es_amigo_de_torre(campo[fila_origen][columna], campo[fila_destino][columna]);
//}
//
//
//bool puede_ir_izquierda_torre(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
//	int i = 0, distancia = 0;
//	if(color_torre(fila, columna_origen, campo) == 't') {
//		distancia = columna_origen - columna_destino;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila][columna_origen - i] != ' ') {
//				break;
//			}
//		}
//	} else {
//		distancia = columna_destino - columna_origen;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila][columna_origen + i] != ' ') {
//				break;
//			}
//		}
//	}
//	return i == distancia && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
//}
//
//bool puede_ir_derecha_torre(int columna_origen, int columna_destino, int fila, char campo[LADO][LADO]) {
//	int i = 0, distancia = 0;
//	if(color_torre(fila, columna_origen, campo) == 't') {
//		distancia = columna_destino - columna_origen;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila][columna_origen + i] != ' ') {
//				break;
//			}
//		}
//	} else {
//		distancia = columna_origen - columna_destino;
//		for(i = 1 ; i < distancia ; i++) {
//			if(campo[fila][columna_origen - i] != ' ') {
//				break;
//			}
//		}
//	}
//	return i == distancia && !es_amigo_de_torre(campo[fila][columna_origen], campo[fila][columna_destino]);
//}
//
//
//bool movimiento_permitido_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]) {
//	if(es_arriba_de_torre(fila_origen, columna_origen,  fila_destino, campo)) {
//		return puede_ir_arriba_torre(fila_origen, fila_destino, columna_origen, campo);
//	} else if(es_abajo_de_torre(fila_origen, columna_origen,  fila_destino, campo)) {
//		return puede_ir_abajo_torre(fila_origen, fila_destino, columna_origen, campo);
//	} else if(es_a_la_derecha_de_torre(fila_origen, columna_origen, columna_destino, campo)) {
//		return puede_ir_derecha_torre(columna_origen, columna_destino, fila_origen, campo);
//	} else if(es_a_la_izquierda_de_torre(fila_origen, columna_origen, columna_destino, campo)) {
//		return puede_ir_izquierda_torre(columna_origen, columna_destino, fila_origen, campo);
//	} else
//		return false;
//}
//
//
