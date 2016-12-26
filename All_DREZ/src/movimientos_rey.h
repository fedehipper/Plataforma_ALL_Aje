#ifndef MOVIMIENTOS_REY_H_
#define MOVIMIENTOS_REY_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_rey(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_hacke_rey(int fila_origen, int columna_origen, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_REY_H_ */
