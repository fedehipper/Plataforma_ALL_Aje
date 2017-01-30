#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "../src/tablero_grafico.h"


#define LADO 8

static FILE* temp_file = NULL;

int init_suite1(void) {
   return NULL == (temp_file = fopen("temp.txt", "w+")) ? -1 : 0;
}

int clean_suite1(void) {
   if (0 != fclose(temp_file)) return -1;
   else {
      temp_file = NULL;
      return 0;
   }
}

// un test
void test_valor(void) {
   int valor = 10;
   CU_ASSERT(10 == valor);
}

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





