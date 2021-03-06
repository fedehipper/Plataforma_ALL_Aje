#ifndef MOVIMIENTOS_TORRE_H_
#define MOVIMIENTOS_TORRE_H_

#define LADO 8
#include <stdbool.h>

bool es_abajo_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool es_amigo_de_torre(char torre, char otro);
bool movimiento_permitido_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool es_jaque_torre(char pieza, int fila_d, int columna_d, int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n, char campo[LADO][LADO]);
bool si_se_mueve_es_jaque_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n);
bool es_arriba_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool es_a_la_izquierda_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool es_a_la_derecha_de_torre(int fila_o, int columna_o, int fila_d, int columna_d, char campo[LADO][LADO]);
bool puede_ir_arriba_torre(int fila_o, int fila_d, int columna, char campo[LADO][LADO]);
bool puede_ir_abajo_torre(int fila_o, int fila_d, int columna, char campo[LADO][LADO]);
bool puede_ir_derecha_torre(int fila_o, int fila_d, int columna, char campo[LADO][LADO]);
bool puede_ir_izquierda_torre(int fila_o, int fila_d, int columna, char campo[LADO][LADO]);


#endif /* MOVIMIENTOS_TORRE_H_ */
