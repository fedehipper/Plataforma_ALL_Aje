#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "../src/tablero_grafico.h"

#define LADO 8

void test_tablero_en_blanco(void) {
	char tablero[LADO][LADO];
	tablero_en_blanco(tablero);
	int i, j;
	bool esta_en_blanco = true;
	for(i = 0 ; i < LADO ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(tablero[i][j] != ' ') esta_en_blanco = false;
		}
	}
	CU_ASSERT(esta_en_blanco);
}

void test_inicializar_posicion_piezas(void) {
	char tablero[LADO][LADO];
	tablero_en_blanco(tablero);
	inicializar_posicion_piezas(tablero);
	bool inicializacion_tablero = tablero[0][0] == 'T' && tablero[0][1] == 'C' && tablero[0][2] == 'A' && tablero[0][3] == 'W' &&
		tablero[0][4] == 'R' && tablero[0][5] == 'A' && tablero[0][6] == 'C' && tablero[0][7] == 'T' && tablero[1][0] == 'P' &&
		tablero[1][1] == 'P' && tablero[1][2] == 'P' && tablero[1][4] == 'P' && tablero[1][5] == 'P' && tablero[1][6] == 'P' &&
		tablero[1][7] == 'P' && tablero[7][0] == 't' && tablero[7][1] == 'c' && tablero[7][2] == 'a' && tablero[7][3] == 'w' &&
		tablero[7][4] == 'r' && tablero[7][5] == 'a' && tablero[7][6] == 'c' && tablero[7][7] == 't' && tablero[6][0] == 'p' &&
		tablero[6][1] == 'p' && tablero[6][2] == 'p' && tablero[6][4] == 'p' && tablero[6][5] == 'p' && tablero[6][6] == 'p' &&
		tablero[6][7] == 'p';
	int i, j;
	for(i = 2 ; i < LADO - 2 ; i++) {
		for(j = 0 ; j < LADO ; j++) {
			if(tablero[i][j] != ' ') {
				inicializacion_tablero = false;
				break;
			}
		}
	}
	CU_ASSERT(inicializacion_tablero);
}





