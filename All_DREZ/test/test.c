#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "test_tablero_grafico.h"
#include "test_movimientos_torre.h"

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

CU_EXPORT CU_ErrorCode clean_up_get_registry(void) {
	CU_cleanup_registry();
	return CU_get_error();
}

CU_EXPORT CU_ErrorCode run_test(void) {
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if(NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	/* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
	if(NULL == CU_add_test(pSuite, "test of test_tablero_en_blanco()", test_tablero_en_blanco)) clean_up_get_registry();
	if(NULL == CU_add_test(pSuite, "test of test_inicializar_posicion_piezas()", test_inicializar_posicion_piezas)) clean_up_get_registry();
	if(NULL == CU_add_test(pSuite, "test of test_es_amigo_de_torre()", test_es_amigo_de_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(pSuite, "test of test_es_abajo_de_torre()", test_es_abajo_de_torre)) clean_up_get_registry();

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();

}
