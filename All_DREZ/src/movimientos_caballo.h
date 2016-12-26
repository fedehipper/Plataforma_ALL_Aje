#ifndef MOVIMIENTOS_CABALLO_H_
#define MOVIMIENTOS_CABALLO_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_caballo(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_hacke_caballo(int fila_origen, int columna_origen, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_CABALLO_H_ */
