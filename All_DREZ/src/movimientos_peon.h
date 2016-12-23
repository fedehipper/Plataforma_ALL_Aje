#ifndef MOVIMIENTOS_PEON_H_
#define MOVIMIENTOS_PEON_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_peon(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_PEON_H_ */
