#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "datos.h"

int main()
{

    // Ruta del archivo tuberia
    char *tuberia = "./mainLectura";
    char *tuberia2 = "./lecturaMain";

    // Crear un archivo de tipo fifo
    mkfifo(tuberia, 0666);

    for (int potencia = 0; potencia < 6; potencia++)
    {

        int tamano = 1000 * pow(10, potencia) * sizeof(char);
        // Se aparta memoria de la informacion a enviar
        char *buffer = malloc(tamano);
        
        int r = escribirTuberia(tuberia,buffer,tamano);

        printf("Tamano mensaje enviado %d\n", r);
        char * confirmacion; 
        leerTuberia(tuberia2,confirmacion,2);
        printf("La lectura del mensaje fue %s",confirmacion);

    }
    // unlink(tuberia);
    // unlink(tuberia2);
    return 0;
}