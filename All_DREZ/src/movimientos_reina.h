#ifndef MOVIMIENTOS_REINA_H_
#define MOVIMIENTOS_REINA_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_reina(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_jaque_reina(char pieza, int fila_destino, int columna_destino, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]);
bool si_se_mueve_es_jaque_reina(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n);


#endif /* MOVIMIENTOS_REINA_H_ */
