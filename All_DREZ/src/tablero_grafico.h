#ifndef TABLERO_GRAFICO_H_
#define TABLERO_GRAFICO_H_

#define LADO 8

void inicializar_posicion_piezas(char campo[LADO][LADO]);
void draw_tablero(void);
void re_draw(char campo[LADO][LADO]);
void tablero_en_blanco(char campo[LADO][LADO]);
void crear_piezas(void);

#endif /* TABLERO_GRAFICO_H_ */