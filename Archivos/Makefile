all : ejecutarMain

ejecutarMain: compilarMain crearTerminal main
	./main

compilarMain: main.c
	gcc main.c -o main -lm

compilarLectura: lectura.c
	gcc lectura.c -o lectura -lm

crearTerminal: compilarLectura
	gnome-terminal -- ./lectura

ejecutarLectura: compilarLectura lectura
	./lectura

clean:
	rm -r main lectura respuesta.txt salida.txt