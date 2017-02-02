#ifndef MOVIMIENTOS_REY_H_
#define MOVIMIENTOS_REY_H_

#include <stdbool.h>
#define LADO 8

bool movimiento_permitido_rey(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool es_jaque_rey(char pieza, int fila_d, int columna_d, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]);
bool me_hacen_jaque(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool es_jaque_mate(int fila_o, int columna_o, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_REY_H_ */
