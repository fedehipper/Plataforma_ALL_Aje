#include <allegro.h>
#include "tablero_grafico.h"
#define LADO 8
#define CURSOR 2

SAMPLE * instalar_sonidos(void) {
	int driver_digi = 1, driver_midi = 0;
	detect_digi_driver(driver_digi);
	detect_midi_driver(driver_midi);
	reserve_voices(5, 5);
	install_sound(driver_digi, driver_midi, "cfg_path");
	set_volume(200, 100);
	return load_sample("mover.wav");
}

void instalar_complementos(void) {
	install_mouse();
	install_timer();
	show_os_cursor(CURSOR);
}

void mostrar_display(void) {
	set_gfx_mode(GFX_SAFE, 870, 667, 0, 0);
}

void desinstalar_complementos(SAMPLE * sonido) {
	remove_mouse();
	remove_timer();
	destroy_sample(sonido);
}

void inicializar_tablero(BITMAP *pantalla, char campo[LADO][LADO]) {
	crear_piezas();
	draw_tablero(pantalla);
	tablero_en_blanco(campo);
	inicializar_posicion_piezas(campo);
	re_draw(pantalla, campo);
}
