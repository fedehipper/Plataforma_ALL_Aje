#ifndef MOVIMIENTOS_ALFIL_H_
#define MOVIMIENTOS_ALFIL_H_

#include <stdbool.h>

#define LADO 8

bool movimiento_permitido_alfil(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_jaque_alfil(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_ALFIL_H_ */
