HEADERS = src/inicializar.h src/jugabilidad.h src/lib_socket.h src/movimientos_alfil.h src/movimientos_caballo.h src/movimientos_peon.h src/movimientos_reina.h src/movimientos_rey.h src/movimientos_torre.h src/tablero_grafico.h src/piezas.h test/test.h test/test_movimientos_torr.h test/test_tablero_grafico.h

ajedrez : src/main.o src/inicializar.o src/jugabilidad.o src/lib_socket.o src/movimientos_alfil.o src/movimientos_caballo.o src/movimientos_peon.o src/movimientos_reina.o src/movimientos_rey.o src/movimientos_torre.o src/tablero_grafico.o test/test_tablero_grafico.o test/test.o test/test_movimientos_torre.o
	gcc -o src/ajedrez src/main.o src/inicializar.o src/jugabilidad.o src/lib_socket.o src/movimientos_alfil.o src/movimientos_caballo.o src/movimientos_peon.o src/movimientos_reina.o src/movimientos_rey.o src/movimientos_torre.o src/tablero_grafico.o test/test_tablero_grafico.o test/test.o test/test_movimientos_torre.o -lalleg -lm -lpthread -lcunit

inicializar.o : src/inicializar.c $(HEADERS)
	gcc -c src/inicializar.c

jugabilidad.o : src/jugabilidad.c $(HEADERS)
	gcc -c src/jugabilidad.c

lib_socket.o : src/lib_socket.c $(HEADERS)
	gcc -c src/lib_socket.c

main.o : src/main.c $(HEADERS)
	gcc -c src/main.c

movimientos_alfil.o : src/movimientos_caballo.o src/movimientos_peon.o src/movimientos_reina.o src/movimientos_rey.o src/movimientos_torre.o
	gcc -c src/movimientos_alfil.c

movimientos_caballo.o : src/movimientos_peon.o src/movimientos_reina.o src/movimientos_rey.o src/movimientos_torre.o
	gcc -c src/movimientos_caballo.c

movimientos_peon.o : src/movimientos_reina.o src/movimientos_rey.o src/movimientos_torre.o
	gcc -c src/movimientos_peon.c

movimientos_reina.o : src/movimientos_rey.o src/movimientos_torre.o
	gcc -c src/movimientos_reina.c

movimientos_rey.o : src/movimientos_torre.o
	gcc -c src/movimientos_rey.c

movimientos_torre.o : 
	gcc -c src/movimientos_torre.c

tablero_grafico.o : $(HEADERS)
	gcc -c src/tablero_grafico.c -lalleg

test_movimientos_torre.o : test/test_movimientos_torre.c
	gcc -c test/test_movimientos_torre.c

test_tablero_grafico.o : test/test_tablero_grafico.c
	gcc -c test/test_tablero_grafico.c -lcunit

test.o : test/test.c
	gcc -c test/test.c -lcunit

clean:
	rm -f src/ajedrez \
		src/main.o src/inicializar.o src/jugabilidad.o src/lib_socket.o src/movimientos_alfil.o src/movimientos_caballo.o src/movimientos_peon.o src/movimientos_reina.o src/movimientos_rey.o src/movimientos_torre.o src/tablero_grafico.o test/test.o test/test_tablero_grafico.o test/test_movimientos_torre.o src/temp.txt
