all : ejecutarMain

ejecutarMain: compilarMain main
	./main

compilarMain: main.c
	gcc main.c -o main -lm

clean:
	rm -r main lectura