#ifndef COMPORTAMIENTO_COMUN_PIEZAS_H_
#define COMPORTAMIENTO_COMUN_PIEZAS_H_

#include <stdbool.h>
#define LADO 8

bool rutina_case_jaque(char pieza, int i, int j, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n);

#endif /* COMPORTAMIENTO_COMUN_PIEZAS_H_ */
