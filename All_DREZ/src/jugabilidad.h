#ifndef JUGABILIDAD_H_
#define JUGABILIDAD_H_

#define LADO 8

void seleccionar(char campo[LADO][LADO], SAMPLE * sonido_mover, BITMAP * pantalla);
void seleccionar_en_red(char campo[LADO][LADO], SAMPLE * sonido_mover, BITMAP * pantalla, char modo_cliente_o_servidor, int *socket_servidor);

#endif /* JUGABILIDAD_H_ */
