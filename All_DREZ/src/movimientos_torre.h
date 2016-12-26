#ifndef MOVIMIENTOS_TORRE_H_
#define MOVIMIENTOS_TORRE_H_

bool movimiento_permitido_torre(int fila_origen, int columna_origen, int fila_destino, int columna_destino, char campo[LADO][LADO]);
bool es_hacke_torre(int fila_origen, int columna_origen, char campo[LADO][LADO]);

#endif /* MOVIMIENTOS_TORRE_H_ */
