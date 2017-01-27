#ifndef TABLERO_GRAFICO_H_
#define TABLERO_GRAFICO_H_

#define LADO 8
#include <stdbool.h>

void inicializar_posicion_piezas(char campo[LADO][LADO]);
void draw_tablero(BITMAP *pantalla);
void tablero_en_blanco(char campo[LADO][LADO]);
void crear_piezas(void);
void draw_cuadrado(int fila, int columna, char campo[LADO][LADO], int color_claro, int color_oscuro, BITMAP * pantalla);
void dibujar_peon_en_movimiento(BITMAP * pantalla, char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_torre_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_caballo_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_alfil_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_reina_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void dibujar_rey_en_movimiento(BITMAP * pantalla,char pieza, int x, int y, char campo[LADO][LADO]);
void liberar_memoria_piezas(BITMAP * pantalla);
void menu(BITMAP * pantalla, int mouse_y, int mouse_x, int *arr);
void menu_seleccion_promocion(BITMAP *pantalla, int mouse_x, int mouse_y, bool seleccion);
void menu_blanco_y_negro(BITMAP *pantalla, int * arr, bool *derecha);
void menu_seleccion_cerrar(BITMAP * pantalla, int mouse_x, int mouse_y, bool seleccion);
void menu_blanco_piezas_promocion(BITMAP *pantalla, int * arr, bool *derecha);
void menu_negro_piezas_promocion(BITMAP *pantalla, int * arr, bool *derecha);
void menu_seleccion_blanco(BITMAP * pantalla, int mouse_x, int mouse_y, bool seleccion, bool derecha);
void seleccionar_promocion(BITMAP * pantalla, int mouse_x, int mouse_y, char *pieza_seleccionada, bool turno_blanca);
void dibujar_seleccion_promocion(BITMAP *pantalla, char pieza_promocion_blanca, char pieza_promocion_negra);
void switcheo_draw_piezas(BITMAP * pantalla, char pieza, char campo[LADO][LADO]);
void re_draw(BITMAP * pantalla, char campo[LADO][LADO]);
void draw_cuadrado_relleno(int fila, int columna, char campo[LADO][LADO], int color,  BITMAP * pantalla);


#endif /* TABLERO_GRAFICO_H_ */
