all : ejecutarMain

ejecutarMain: compilarMain crearTerminal main
	./main

compilarMain: main.c
	gcc main.c -o main -lm


compilaLectura: lectura.c
	gcc lectura.c -o lectura -lm

crearTerminal: compilaLectura
	gnome-terminal -- ./lectura

clean:
	rm -r main lectura mainLectura lecturaMain