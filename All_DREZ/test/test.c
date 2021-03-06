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
	CU_pSuite p_suite = NULL;

	/* initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	/* add a suite to the registry */
	p_suite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if(NULL == p_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	/* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
	if(NULL == CU_add_test(p_suite, "test of test_tablero_en_blanco()", test_tablero_en_blanco)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_inicializar_posicion_piezas()", test_inicializar_posicion_piezas)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_es_amigo_de_torre()", test_es_amigo_de_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_es_abajo_de_torre()", test_es_abajo_de_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_es_arriba_de_torre()", test_es_arriba_de_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_es_a_la_izquierda_de_torre()", test_es_a_la_izquierda_de_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_es_a_la_derecha_de_torre()", test_es_a_la_derecha_de_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_es_jaque_torre()", test_es_jaque_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_puede_ir_arriba_torre()", test_puede_ir_arriba_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_puede_ir_abajo_torre()", test_puede_ir_abajo_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_puede_ir_izquierda_torre()", test_puede_ir_izquierda_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_puede_ir_derecha_torre()", test_puede_ir_derecha_torre)) clean_up_get_registry();
	if(NULL == CU_add_test(p_suite, "test of test_si_se_mueve_es_jaque_torre()", test_si_se_mueve_es_jaque_torre)) clean_up_get_registry();


	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();

}
