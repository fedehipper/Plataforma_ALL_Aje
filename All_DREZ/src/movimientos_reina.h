#ifndef MOVIMIENTOS_REINA_H_
#define MOVIMIENTOS_REINA_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_reina(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_hacke_reina(int fila_origen, int columna_origen, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_REINA_H_ */
