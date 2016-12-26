#ifndef MOVIMIENTOS_ALFIL_H_
#define MOVIMIENTOS_ALFIL_H_

#include <stdbool.h>

#define LADO 8

bool movimiento_permitido_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_hacke_alfil(int fila_origen, int columna_origen, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_ALFIL_H_ */
