#include <CUnit/Basic.h>
#include "../src/movimientos_torre.h"

#define LADO 8

void test_es_amigo_de_torre(void) {
	CU_ASSERT(es_amigo_de_torre('t', 'c'));
	CU_ASSERT(es_amigo_de_torre('t', 'a'));
	CU_ASSERT(es_amigo_de_torre('t', 't'));
	CU_ASSERT(es_amigo_de_torre('t', 'w'));
	CU_ASSERT(es_amigo_de_torre('t', 'r'));
	CU_ASSERT(es_amigo_de_torre('t', 'p'));
	CU_ASSERT(es_amigo_de_torre('T', 'C'));
	CU_ASSERT(es_amigo_de_torre('T', 'A'));
	CU_ASSERT(es_amigo_de_torre('T', 'T'));
	CU_ASSERT(es_amigo_de_torre('T', 'W'));
	CU_ASSERT(es_amigo_de_torre('T', 'R'));
	CU_ASSERT(es_amigo_de_torre('T', 'P'));
	CU_ASSERT_FALSE(es_amigo_de_torre('T', 'c'));
	CU_ASSERT_FALSE(es_amigo_de_torre('T', 'a'));
	CU_ASSERT_FALSE(es_amigo_de_torre('T', 't'));
	CU_ASSERT_FALSE(es_amigo_de_torre('T', 'w'));
	CU_ASSERT_FALSE(es_amigo_de_torre('T', 'r'));
	CU_ASSERT_FALSE(es_amigo_de_torre('T', 'p'));
	CU_ASSERT_FALSE(es_amigo_de_torre('t', 'C'));
	CU_ASSERT_FALSE(es_amigo_de_torre('t', 'A'));
	CU_ASSERT_FALSE(es_amigo_de_torre('t', 'T'));
	CU_ASSERT_FALSE(es_amigo_de_torre('t', 'W'));
	CU_ASSERT_FALSE(es_amigo_de_torre('t', 'R'));
	CU_ASSERT_FALSE(es_amigo_de_torre('t', 'P'));
}

void inicializar_campo(char campo[LADO][LADO]) {
	int i, j;
	for(i = 0 ; i < LADO ; i++) for(j = 0 ; j < LADO ; j++) campo[i][j] = ' ';
}

void test_es_abajo_de_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[2][2] = 't';
	campo[4][4] = 'T';
	CU_ASSERT(es_abajo_de_torre(4, 4 , 2, 4 ,campo));
	CU_ASSERT(es_abajo_de_torre(2, 2, 4, 2 ,campo));
	CU_ASSERT_FALSE(es_abajo_de_torre(4, 4, 5, 4, campo));
	CU_ASSERT_FALSE(es_abajo_de_torre(2, 2, 1, 2, campo));
	CU_ASSERT_FALSE(es_abajo_de_torre(2, 2, 3, 4, campo));
	CU_ASSERT_FALSE(es_abajo_de_torre(4, 4, 4, 3, campo));
}

void test_es_arriba_de_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[2][2] = 't';
	campo[4][4] = 'T';
	CU_ASSERT(es_arriba_de_torre(2, 2, 1, 2, campo));
	CU_ASSERT(es_arriba_de_torre(4, 4, 5, 4, campo));
}

void test_es_a_la_izquierda_de_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[2][2] = 't';
	campo[4][4] = 'T';
	CU_ASSERT(es_a_la_izquierda_de_torre(2, 2, 2, 1, campo));
	CU_ASSERT(es_a_la_izquierda_de_torre(4, 4, 4, 5, campo));
}

void test_es_a_la_derecha_de_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[2][2] = 't';
	campo[4][4] = 'T';
	CU_ASSERT(es_a_la_derecha_de_torre(2, 2, 2, 3, campo));
	CU_ASSERT(es_a_la_derecha_de_torre(4, 4, 4, 3, campo));
}

void test_es_jaque_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	CU_ASSERT(es_jaque_torre('t', 4, 4, 0, 0, 5, 4, campo));
	CU_ASSERT(es_jaque_torre('T', 4, 4, 5, 4, 0, 0, campo));
}

void test_puede_ir_arriba_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[3][4] = 't';
	campo[5][5] = 'T';
	CU_ASSERT(puede_ir_arriba_torre(3, 2, 4, campo));
	CU_ASSERT(puede_ir_arriba_torre(5, 7, 5, campo));
}

void test_puede_ir_abajo_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[3][4] = 't';
	campo[5][5] = 'T';
	CU_ASSERT(puede_ir_abajo_torre(3, 5, 4, campo));
	CU_ASSERT(puede_ir_abajo_torre(5, 4, 5, campo));
}

void test_puede_ir_derecha_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[3][4] = 't';
	campo[5][5] = 'T';
	CU_ASSERT(puede_ir_derecha_torre(4, 6, 3, campo));
	CU_ASSERT(puede_ir_derecha_torre(5, 2, 5, campo));
}

void test_puede_ir_izquierda_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[3][4] = 't';
	campo[5][5] = 'T';
	CU_ASSERT(puede_ir_izquierda_torre(4, 2, 3, campo));
	CU_ASSERT(puede_ir_izquierda_torre(5, 6, 5, campo));
}

void test_si_se_mueve_es_jaque_torre(void) {
	char campo[LADO][LADO];
	inicializar_campo(campo);
	campo[1][0] = 't';
	campo[6][7] = 'T';
	campo[6][0] = 'W';
	campo[0][7] = 'w';
	CU_ASSERT(si_se_mueve_es_jaque_torre(1, 0 , 6, 1, campo, 0, 0, 7, 7));
	CU_ASSERT(si_se_mueve_es_jaque_torre(6, 7 , 6, 6, campo, 0, 0, 7, 7));
}
