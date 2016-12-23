#include <stdbool.h>

#define LADO 8

bool es_amigo_de_rey(char rey, char otro) {
	if(rey == 'r') {
		return otro == 'w' || otro == 'a' || otro == 'r' || otro == 't' || otro == 'c' || otro == 'p';
	} else {
		return otro == 'W' || otro == 'A' || otro == 'R' || otro == 'T' || otro == 'C' || otro == 'P';
	}
}

char color_rey(int fila_origen, int columna_origen, char campo[LADO][LADO]) {
	return campo[fila_origen][columna_origen];
}

bool es_superior_a_rey(int fila_origen, int fila_destino, int columna, char campo[LADO][LADO]) {

}

bool es_inferior_a_rey() {}

bool es_izquierda_a_rey() {}

bool es_derecha_a_rey() {}

bool es_superior_derecho_a_rey() {}

bool es_superior_izquierdo_a_rey() {}

bool es_inferior_derecho_a_rey() {}

bool es_inferior_izquierdo_a_rey() {}


bool puede_ir_arriba_rey() {}

bool puede_ir_abajo_rey() {}

bool puede_ir_izquierda_rey() {}

bool puede_ir_derecha_rey() {}

bool puede_ir_superior_derecha_rey() {}

bool puede_ir_superior_izquierda_rey() {}

bool puede_ir_inferior_derecha_rey() {}

bool puede_ir_inferior_izquierda_rey() {}

bool movimiento_permitido_rey() {}


