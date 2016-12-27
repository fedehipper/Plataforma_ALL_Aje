#ifndef MOVIMIENTOS_CABALLO_H_
#define MOVIMIENTOS_CABALLO_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_caballo(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_jaque_caballo(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]);
bool si_se_mueve_es_jaque_caballo(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n);


#endif /* MOVIMIENTOS_CABALLO_H_ */
