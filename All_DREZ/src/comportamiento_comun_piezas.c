#include <stdbool.h>
#include "movimientos_peon.h"
#include "movimientos_caballo.h"
#include "movimientos_rey.h"
#include "movimientos_torre.h"
#include "movimientos_alfil.h"
#include "movimientos_reina.h"

#define LADO 8

bool rutina_case_jaque(char pieza, int i, int j, char campo[LADO][LADO], int f_rey_b, int c_rey_b, int f_rey_n, int c_rey_n) {
	bool es_jaque = false;
	switch(pieza) {
		case 'p': case 'P': if(es_jaque_peon(pieza, i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
		case 'a': case 'A': if(es_jaque_alfil(pieza, i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n,campo)) es_jaque = true; break;
		case 't': case 'T': if(es_jaque_torre(pieza, i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
		case 'c': case 'C': if(es_jaque_caballo(pieza, i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
		case 'w': case 'W': if(es_jaque_reina(pieza, i, j, f_rey_b, c_rey_b, f_rey_n, c_rey_n, campo)) es_jaque = true; break;
	}
	return es_jaque;
}
