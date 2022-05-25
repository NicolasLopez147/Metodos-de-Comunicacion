#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "datos.h"

#define KILOB 1000

int main()
{   
    // Ruta del archivo tuberia
    char *tuberia = "./tuberia";
    char *tuberia2 = "./tuberia2";

    for (int potencia = 0 ; potencia < 6 ; potencia ++){
        int limite = 50;

        for (int i = 0 ; i < limite ; i ++){
            int tamano = KILOB * pow(10, potencia) * sizeof(char);
            char * buffer = malloc(tamano);
            int cantidad = leerTuberia(tuberia,buffer,tamano);

            printf("Bytes leidos %d iteracion %d\n",cantidad,i);
            unlink(tuberia);

            free(buffer);
            mkfifo(tuberia2,0666);
            char confirmacion [] = "OK";

            cantidad = escribirTuberia(tuberia2,confirmacion,2);
        }
    }
}