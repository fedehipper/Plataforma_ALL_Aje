#define LADO 8
#define CARACTER_A_ENTERO 97

void avanzar_uno(int fila, char columna, char jugador, char campo[LADO][LADO]) {
	int fila_real = fila - 1;
	campo[fila_real][columna - CARACTER_A_ENTERO] = ' ';
	if(jugador == 'B') {
		campo[fila_real + 1][columna - CARACTER_A_ENTERO] = 'p';
	} else {
		campo[fila_real - 1][columna - CARACTER_A_ENTERO] = 'P';
	}
}

//void avanzar_dos_inicial(int fila, char columna, char jugador, char campo[LADO][LADO]) {
//
//}
