SOURCES = inicializar.c jugabilidad.c lib_socket.c main.c movimientos_alfil.c movimientos_caballo.c movimientos_peon.c movimientos_reina.c movimientos_rey.c movimientos_torre.c tablero_grafico.c

HEADERS = inicializar.h jugabilidad.h lib_socket.h movimientos_alfil.h movimientos_caballo.h movimientos_peon.h movimientos_reina.h movimientos_rey.h movimientos_torre.h tablero_grafico.h piezas.h

ajedrez : main.o inicializar.o jugabilidad.o lib_socket.o movimientos_alfil.o movimientos_caballo.o movimientos_peon.o movimientos_reina.o movimientos_rey.o movimientos_torre.o tablero_grafico.o
	gcc -o ajedrez main.o inicializar.o jugabilidad.o lib_socket.o movimientos_alfil.o movimientos_caballo.o movimientos_peon.o movimientos_reina.o movimientos_rey.o movimientos_torre.o tablero_grafico.o -lalleg -lm -lpthread

inicializar.o : inicializar.c $(HEADERS)
	gcc -c inicializar.c

jugabilidad.o : jugabilidad.c $(HEADERS)
	gcc -c jugabilidad.c

lib_socket.o : lib_socket.c $(HEADERS)
	gcc -c lib_socket.c

main.o : main.c $(HEADERS)
	gcc -c main.c

movimientos_alfil.o : movimientos_caballo.o movimientos_peon.o movimientos_reina.o movimientos_rey.o movimientos_torre.o
	gcc -c movimientos_alfil.c

movimientos_caballo.o : movimientos_peon.o movimientos_reina.o movimientos_rey.o movimientos_torre.o
	gcc -c movimientos_caballo.c

movimientos_peon.o : movimientos_reina.o movimientos_rey.o movimientos_torre.o
	gcc -c movimientos_peon.c

movimientos_reina.o : movimientos_rey.o movimientos_torre.o
	gcc -c movimientos_reina.c

movimientos_rey.o : movimientos_torre.o
	gcc -c movimientos_rey.c

movimientos_torre.o : 
	gcc -c movimientos_torre.c

tablero_grafico.o : $(HEADERS)
	gcc -c tablero_grafico.c -lalleg

clean:
	rm -f ajedrez \
		main.o inicializar.o jugabilidad.o lib_socket.o movimientos_alfil.o movimientos_caballo.o movimientos_peon.o movimientos_reina.o movimientos_rey.o movimientos_torre.o tablero_grafico.o

send : tar zcvf snake.tar $(SOURCES) $(HEADERS) Makefile
