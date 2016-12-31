#ifndef TABLERO_GRAFICO_H_
#define TABLERO_GRAFICO_H_

#define LADO 8
#include <stdbool.h>

void inicializar_posicion_piezas(char campo[LADO][LADO]);
void draw_tablero(BITMAP *pantalla);
void re_draw(BITMAP * pantalla, char campo[LADO][LADO]);
void tablero_en_blanco(char campo[LADO][LADO]);
void crear_piezas(void);
void draw_cuadrado(int fila, int columna, char campo[LADO][LADO], int color_claro, int color_oscuro, bool dibujar_pieza, BITMAP * pantalla);
void dibujar_peon_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_torre_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_caballo_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_alfil_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_reina_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_rey_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void liberar_memoria_piezas(BITMAP * pantalla);

#endif /* TABLERO_GRAFICO_H_ */
