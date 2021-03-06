#ifndef INICIALIZAR_H_
#define INICIALIZAR_H_

#include <allegro.h>

SAMPLE * instalar_sonidos(void);
void instalar_complementos(void);
void mostrar_display(void);
void inicializar_tablero(BITMAP * pantalla, char campo[LADO][LADO]);
void desinstalar_complementos(SAMPLE * sonido);

#endif /* INICIALIZAR_H_ */
