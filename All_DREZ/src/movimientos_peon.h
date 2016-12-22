#ifndef MOVIMIENTOS_PEON_H_
#define MOVIMIENTOS_PEON_H_

#include <stdbool.h>

void avanzar_uno(char fila, int columna, char jugador, char campo[LADO][LADO]);
bool movimiento_permitido(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);


#endif /* MOVIMIENTOS_PEON_H_ */
